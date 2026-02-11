key_adrfil_hashes_generic(void *arg, const char *value_,
                                              const int former) {
  hash_struct *const hash = (hash_struct*) arg;
  const lien_url*const lien = (lien_url*) value_;
  const char *const adr = !former ? lien->adr : lien->former_adr;
  const char *const fil = !former ? lien->fil : lien->former_fil;
  const char *const adr_norm = adr != NULL ?
    ( hash->normalized  ? jump_normalized(adr) : jump_identification(adr) )
    : NULL;


  assertf(adr_norm != NULL);
  strcpy(hash->normfil, adr_norm);


  assertf(fil != NULL);
  if (hash->normalized) {
    fil_normalized(fil, &hash->normfil[strlen(hash->normfil)]);
  } else {
    strcpy(&hash->normfil[strlen(hash->normfil)], fil);
  }


  return inthash_hash_value(hash->normfil);
}
