udf_fopen(udf_dirent_t *p_udf_root, const char *psz_name)
{
  udf_dirent_t *p_udf_file = NULL;

  if (p_udf_root) {
    char tokenline[udf_MAX_PATHLEN];
    char *psz_token;

    strncpy(tokenline, psz_name, udf_MAX_PATHLEN);
    psz_token = strtok(tokenline, udf_PATH_DELIMITERS);
    if (psz_token) {


      udf_dirent_t *p_udf_dirent =
	udf_new_dirent(&p_udf_root->fe, p_udf_root->p_udf,
		       p_udf_root->psz_name, p_udf_root->b_dir,
		       p_udf_root->b_parent);
      p_udf_file = udf_ff_traverse(p_udf_dirent, psz_token);
      udf_dirent_free(p_udf_dirent);
    }
    else if ( 0 == strncmp("/", psz_name, sizeof("/")) ) {
      return udf_new_dirent(&p_udf_root->fe, p_udf_root->p_udf,
			    p_udf_root->psz_name, p_udf_root->b_dir,
			    p_udf_root->b_parent);
    }
  }
  return p_udf_file;
}
