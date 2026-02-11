sge_getenv(const char *env_str)
{
   const char *cp=NULL;

   DENTER_(BASIS_LAYER, "sge_getenv");

   cp = (char *) getenv(env_str);

   DRETURN_(cp);
}
