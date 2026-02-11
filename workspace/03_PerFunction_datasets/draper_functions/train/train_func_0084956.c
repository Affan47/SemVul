auth_token_convert(FILE *fp, Auth_token_mode required_mode)
{
  int linenum;
  char *errmsg, *line;
  Auth_token *token;
  Ds *ds;

  ds = ds_init(NULL);
  dsio_set(ds, fp, NULL, 0, 0);

  linenum = 1;
  errmsg = NULL;
  while ((line = dsio_gets(ds)) != NULL) {
	if ((token = auth_token_old_unflatten(line)) == NULL) {
	  errmsg = "Cannot import record";
	  goto fail;
	}

	if (required_mode == TOKEN_MODE_UNKNOWN
		|| token_mode(token->mode, required_mode)) {
	  if (export_token(stdout, token) == -1) {
		errmsg = "Export failed";
		goto fail;
	  }
	}

	linenum++;
  }

  if (ferror(fp) || !feof(fp)) {
	errmsg = "Input error";
	goto fail;
  }

  return(0);

 fail:
  if (errmsg == NULL)
	fprintf(stderr, "Error at line %d: syntax error", linenum);
  else
	fprintf(stderr, "Line %d: %s", linenum, errmsg);
  if (line != NULL)
	fprintf(stderr, ": %s", line);
  fprintf(stderr, "\n");

  return(-1);
}
