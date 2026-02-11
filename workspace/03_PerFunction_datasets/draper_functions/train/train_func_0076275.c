do_passwd(int argc, char **argv)
{
  int rc;
  Cookie *c, *cookies;
  Cred_cache *cache;
  Ds ds;
  FILE *fp, *nfp;

  if ((fp = cookie_cache_open()) == NULL)
	return(-1);

  if ((cache = cookie_cache_load(fp)) == NULL
	  || (cookies = cache->cookies) == NULL) {
	ds_fclose(fp);
	return(0);
  }

  rc = -1;
  nfp = NULL;

  ds_init(&ds);
  ds.clear_flag = 1;
  for (c = cookies; c != NULL; c = c->next) {
	ds_asprintf(&ds, "%s\n", c->str);
  }

  if (cache_write(fp, cachefile, "New DACS Cache Password: ", &ds) == -1)
	goto done;

  rc = 0;

 done:

  ds_free(&ds);

  return(rc);
}
