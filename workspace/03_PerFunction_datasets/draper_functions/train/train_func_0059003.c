mailimap_capability_parse(mailstream * fd, MMAPString * buffer,
			  size_t * indx,
			  struct mailimap_capability ** result,
			  size_t progr_rate,
			  progress_function * progr_fun)
{
  size_t cur_token;
  int type;
  char * auth_type;
  char * atom;
  struct mailimap_capability * cap;
  int r;
  int res;

  cur_token = * indx;

  auth_type = NULL;
  atom = NULL;

  r = mailimap_token_case_insensitive_parse(fd, buffer, &cur_token, "AUTH=");
  switch (r) {
  case MAILIMAP_NO_ERROR:
    type = MAILIMAP_CAPABILITY_AUTH_TYPE;

    r = mailimap_auth_type_parse(fd, buffer, &cur_token, &auth_type,
				 progr_rate, progr_fun);
    if (r != MAILIMAP_NO_ERROR) {
      res = r;
      goto err;
    }
    break;

  case MAILIMAP_ERROR_PARSE:
    r = mailimap_atom_parse(fd, buffer, &cur_token, &atom,
			    progr_rate, progr_fun);
    if (r != MAILIMAP_NO_ERROR) {
      res = r;
      goto err;
    }

    type = MAILIMAP_CAPABILITY_NAME;
    break;

  default:
    res = r;
    goto err;
  }

  cap = mailimap_capability_new(type, auth_type, atom);
  if (cap == NULL) {
    res = MAILIMAP_ERROR_MEMORY;
    goto free;
  }

  * result = cap;
  * indx = cur_token;

  return MAILIMAP_NO_ERROR;

 free:
  if (auth_type)
    mailimap_auth_type_free(auth_type);
  if (atom)
    mailimap_atom_free(atom);
 err:
  return res;
}
