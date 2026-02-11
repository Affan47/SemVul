sic_read(Vfs_handle *h, char *hashstr, char *username)
{
  int st;
  char *key;
  Sic_entry *sic;

  st = 0;
  key = NULL;
  if (hashstr != NULL) {
	if ((st = sic_exists_hashstr_entry(h, hashstr)) == -1) {
	  log_msg((LOG_DEBUG_LEVEL, "Cannot find entry for digest \"%s\"",
			   hashstr));
	  return(NULL);
	}
	if (st == 1)
	  key = sic_make_key_from_hashstr(hashstr);
  }

  if (st == 0 && username != NULL) {
	if ((st = sic_exists_username_entry(h, username)) == -1) {
	  log_msg((LOG_DEBUG_LEVEL, "Cannot read entry for username \"%s\"",
			   username));
	  return(NULL);
	}

	if (st == 1)
	  key = sic_make_key_from_username(username);
  }

  if (st == 0)
	return(NULL);

  if ((sic = sic_read_entry(h, key)) == NULL)
	return(NULL);

  return(sic);
}
