mailimap_body_fld_param_parse(mailstream * fd,
			      MMAPString * buffer, size_t * indx,
			      struct mailimap_body_fld_param ** result,
			      size_t progr_rate,
			      progress_function * progr_fun)
{
  size_t cur_token;
  clist * param_list;
  struct mailimap_body_fld_param * fld_param;
  int r;
  int res;

  param_list = NULL;
  cur_token = * indx;

  r = mailimap_nil_parse(fd, buffer, &cur_token);
  if (r == MAILIMAP_NO_ERROR) {
    * result = NULL;
    * indx = cur_token;
    return MAILIMAP_NO_ERROR;
  }

  if (r != MAILIMAP_ERROR_PARSE) {
    res = r;
    goto err;
  }

  r = mailimap_oparenth_parse(fd, buffer, &cur_token);
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    goto err;
  }

  r = mailimap_struct_spaced_list_parse(fd, buffer, &cur_token, &param_list,
					(mailimap_struct_parser *)
					mailimap_single_body_fld_param_parse,
					(mailimap_struct_destructor *)
					mailimap_single_body_fld_param_free,
					progr_rate, progr_fun);
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    goto err;
  }

  r = mailimap_cparenth_parse(fd, buffer, &cur_token);
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    goto free;
  }

  fld_param = mailimap_body_fld_param_new(param_list);
  if (fld_param == NULL) {
    res = MAILIMAP_ERROR_MEMORY;
    goto free;
  }

  * indx = cur_token;
  * result = fld_param;

  return MAILIMAP_NO_ERROR;

 free:
  clist_foreach(param_list,
		(clist_func) mailimap_single_body_fld_param_free,
		NULL);
  clist_free(param_list);
 err:
  return res;
}
