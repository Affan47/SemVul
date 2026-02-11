BL_Unload(void)
{


  char *disableUnload = NULL;
  vector = NULL;


  if (blLib) {
      disableUnload = PR_GetEnv("NSS_DISABLE_UNLOAD");
      if (!disableUnload) {
          PRStatus status = PR_UnloadLibrary(blLib);
          PORT_Assert(PR_SUCCESS == status);
      }
      blLib = NULL;
  }
  loadFreeBLOnce = pristineCallOnce;
}
