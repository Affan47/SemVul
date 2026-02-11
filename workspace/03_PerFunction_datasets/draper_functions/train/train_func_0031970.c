inflate_stream(struct connectdata *conn,
               struct Curl_transfer_keeper *k)
{
  int allow_restart = 1;
  z_stream *z = &k->z;
  uInt nread = z->avail_in;
  Bytef *orig_in = z->next_in;
  int status;
  CURLcode result = CURLE_OK;
  char *decomp;


  decomp = (char*)malloc(DSIZ);
  if (decomp == NULL) {
    return exit_zlib(z, &k->zlib_init, CURLE_OUT_OF_MEMORY);
  }


  for (;;) {

    z->next_out = (Bytef *)decomp;
    z->avail_out = DSIZ;

    status = inflate(z, Z_SYNC_FLUSH);
    if (status == Z_OK || status == Z_STREAM_END) {
      allow_restart = 0;
      if(DSIZ - z->avail_out) {
        result = Curl_client_write(conn, CLIENTWRITE_BODY, decomp,
                                   DSIZ - z->avail_out);

        if (result) {
          free(decomp);
          return exit_zlib(z, &k->zlib_init, result);
        }
      }


      if (status == Z_STREAM_END) {
        free(decomp);
        if (inflateEnd(z) == Z_OK)
          return exit_zlib(z, &k->zlib_init, result);
        else
          return exit_zlib(z, &k->zlib_init, process_zlib_error(conn, z));
      }


      if (status == Z_OK && z->avail_in == 0) {
        free(decomp);
        return result;
      }
    }
    else if (allow_restart && status == Z_DATA_ERROR) {


      inflateReset(z);
      if (inflateInit2(z, -MAX_WBITS) != Z_OK) {
        return process_zlib_error(conn, z);
      }
      z->next_in = orig_in;
      z->avail_in = nread;
      allow_restart = 0;
      continue;
    }
    else {
      free(decomp);
      return exit_zlib(z, &k->zlib_init, process_zlib_error(conn, z));
    }
  }

}
