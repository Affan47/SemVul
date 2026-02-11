_fallback(Eina_Prefix *pfx, const char *pkg_bin, const char *pkg_lib,
          const char *pkg_data, const char *pkg_locale, const char *envprefix)
{
   char *p;

   STRDUP_REP(pfx->prefix_path, pkg_bin);
   if (!pfx->prefix_path) return 0;
   p = strrchr(pfx->prefix_path, DSEP_C);
   if (p) *p = 0;
   STRDUP_REP(pfx->prefix_path_bin, pkg_bin);
   STRDUP_REP(pfx->prefix_path_lib, pkg_lib);
   STRDUP_REP(pfx->prefix_path_data, pkg_data);
   STRDUP_REP(pfx->prefix_path_locale, pkg_locale);
   WRN("Could not determine its installed prefix for '%s'\n"
       "      so am falling back on the compiled in default:\n"
       "        %s\n"
       "      implied by the following:\n"
       "        bindir    = %s\n"
       "        libdir    = %s\n"
       "        datadir   = %s\n"
       "        localedir = %s\n"
       "      Try setting the following environment variables:\n"
       "        %s_PREFIX     - points to the base prefix of install\n"
       "      or the next 4 variables\n"
       "        %s_BIN_DIR    - provide a specific binary directory\n"
       "        %s_LIB_DIR    - provide a specific library directory\n"
       "        %s_DATA_DIR   - provide a specific data directory\n"
       "        %s_LOCALE_DIR - provide a specific locale directory",
       envprefix,
       pfx->prefix_path, pkg_bin, pkg_lib, pkg_data, pkg_locale,
       envprefix, envprefix, envprefix, envprefix, envprefix);
   pfx->fallback = 1;
   return 1;
}
