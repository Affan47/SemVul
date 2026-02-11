g_rc_gschlas_version(SCM scm_version)
{
    char *version;
    SCM ret = SCM_BOOL_T;

    SCM_ASSERT (scm_is_string (scm_version), scm_version,
		SCM_ARG1, "gschlas-version");

    version = scm_to_utf8_string (scm_version);
    if (g_strcasecmp (version, PACKAGE_DATE_VERSION) != 0) {
      fprintf(stderr,
              "You are running gEDA/gaf version [%s%s.%s],\n",
              PREPEND_VERSION_STRING, PACKAGE_DOTTED_VERSION,
              PACKAGE_DATE_VERSION);
      fprintf(stderr,
              "but you have a version [%s] gschlasrc file:\n[%s]\n",
              version, rc_filename);
      fprintf(stderr,
              "Please be sure that you have the latest rc file.\n");
      ret = SCM_BOOL_F;
    }

    free (version);
    return ret;
}
