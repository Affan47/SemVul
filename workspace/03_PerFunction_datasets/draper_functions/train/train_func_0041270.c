_gcry_md_hash_buffer (int algo, void *digest,
                      const void *buffer, size_t length)
{
  if (algo == GCRY_MD_SHA1)
    _gcry_sha1_hash_buffer (digest, buffer, length);
  else if (algo == GCRY_MD_RMD160 && !fips_mode () )
    _gcry_rmd160_hash_buffer (digest, buffer, length);
  else
    {


      gcry_md_hd_t h;
      gpg_err_code_t err;

      if (algo == GCRY_MD_MD5 && fips_mode ())
        {
          _gcry_inactivate_fips_mode ("MD5 used");
          if (_gcry_enforced_fips_mode () )
            {


              _gcry_fips_noreturn ();
            }
        }

      err = md_open (&h, algo, 0);
      if (err)
	log_bug ("gcry_md_open failed for algo %d: %s",
                 algo, gpg_strerror (gcry_error(err)));
      md_write (h, (byte *) buffer, length);
      md_final (h);
      memcpy (digest, md_read (h, algo), md_digest_length (algo));
      md_close (h);
    }
}
