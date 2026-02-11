sge_basename(const char *name, int delim)
{
   char *cp;

   DENTER(BASIS_LAYER, "sge_basename");

   if (!name) {
      DRETURN(NULL);
   }
   if (name[0] == '\0') {
      DRETURN(NULL);
   }

   cp = strrchr(name, delim);
   if (!cp) {
      DRETURN(name);
   } else {
      cp++;
      if (*cp == '\0') {
         DRETURN(NULL);
      }
      else {
         DRETURN(cp);
      }
   }
}
