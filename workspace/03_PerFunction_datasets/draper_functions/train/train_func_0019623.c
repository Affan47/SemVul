gp_init(void)
{

#ifdef USE_DEFAULT_PATHS

  gp_header_path = getenv("GPUTILS_HEADER_PATH");
  gp_lkr_path = getenv("GPUTILS_LKR_PATH");
  gp_lib_path = getenv("GPUTILS_LIB_PATH");

  #ifndef HAVE_DOS_BASED_FILE_SYSTEM
    if (gp_header_path == NULL) {
      gp_header_path = strdup(HEADER_PATH);
    }
    if (gp_lkr_path == NULL) {
      gp_lkr_path = strdup(LKR_PATH);
    }
    if (gp_lib_path == NULL) {
      gp_lib_path = strdup(LIB_PATH);
    }
  #endif

#else
  gp_header_path = NULL;
  gp_lkr_path = NULL;
  gp_lib_path = NULL;
#endif

}
