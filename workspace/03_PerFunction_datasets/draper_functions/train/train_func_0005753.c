auth_grid_unflatten(char *e_grid_str, int decrypt)
{
  char *dstr, *gstr, *grid_str, *pstr, *sstr;
  unsigned int e_len;
  unsigned char *e_str;
  Auth_grid *grid;
  Dsvec *dsv1;
  static Crypt_keys *keys = NULL;

  if (e_grid_str == NULL)
	return(NULL);

  if (decrypt) {
	if (stra64b(e_grid_str, &e_str, &e_len) == NULL) {
	  log_msg((LOG_ERROR_LEVEL, "Base-64 decoding failed"));
	  return(NULL);
	}
	if (keys == NULL
		&& (keys = crypt_keys_from_vfs(inkeys_item_type)) == NULL) {
	  log_msg((LOG_ERROR_LEVEL, "Cannot load keys from item type %s",
			   inkeys_item_type));
	  return(NULL);
	}
	if (crypto_decrypt_string(keys, e_str, e_len,
							  (unsigned char **) &grid_str, NULL) == -1) {
	  log_msg((LOG_ERROR_LEVEL, "Decryption failed"));
	  return(NULL);
	}
  }
  else
	grid_str = e_grid_str;

  grid = auth_grid_new(NULL);
  if ((dsv1 = strsplit(grid_str, ",", 0)) == NULL)
	return(NULL);
  if ((grid->serial = dsvec_ptr(dsv1, 0, char *)) == NULL)
	return(NULL);
  if ((sstr = dsvec_ptr(dsv1, 1, char *)) == NULL)
	return(NULL);
  if (streq(sstr, "1"))
	grid->enabled = 1;
  else
	grid->enabled = 0;

  if ((gstr = dsvec_ptr(dsv1, 2, char *)) == NULL)
	return(NULL);
  if ((grid->grid = strsplit(gstr, " ", 0)) == NULL)
	return(NULL);
  grid->nrows = dsvec_len(grid->grid);
  if (grid->nrows < AUTH_GRID_MIN_ROWS || grid->nrows > AUTH_GRID_MAX_ROWS)
	return(NULL);
  grid->ncols = strlen(dsvec_ptr(grid->grid, 0, char *)) / 3;
  if (grid->ncols < AUTH_GRID_MIN_COLS || grid->ncols > AUTH_GRID_MAX_COLS)
	return(NULL);

  if ((pstr = dsvec_ptr(dsv1, 3, char *)) == NULL)
	return(NULL);
  if (streq(pstr, "0"))
	grid->pin = NULL;
  else
	grid->pin = pstr;

  if ((dstr = dsvec_ptr(dsv1, 4, char *)) == NULL)
	return(NULL);
  if (strnum(dstr, STRNUM_TIME_T, &grid->date_created) == -1)
	return(NULL);

  return(grid);
}
