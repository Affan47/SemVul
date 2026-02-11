generic_cache_delete(struct mail_cache_db * cache_db,
    char * keyname)
{
  int r;
  int res;

  r = mail_cache_db_del(cache_db, keyname, strlen(keyname));
  if (r != 0) {
    res = MAIL_ERROR_FILE;
    goto err;
  }

  return MAIL_NO_ERROR;

 err:
  return res;
}
