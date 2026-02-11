scm_init_load_path ()
{
  char *env;
  SCM path = SCM_EOL;

#ifdef SCM_LIBRARY_DIR
  path = scm_list_3 (scm_from_locale_string (SCM_SITE_DIR),
		     scm_from_locale_string (SCM_LIBRARY_DIR),
		     scm_from_locale_string (SCM_PKGDATA_DIR));
#endif

  env = getenv ("GUILE_LOAD_PATH");
  if (env)
    path = scm_parse_path (scm_from_locale_string (env), path);

  *scm_loc_load_path = path;
}
