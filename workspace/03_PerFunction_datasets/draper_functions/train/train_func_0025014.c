sge_strafree(char ***cpp)
{
   if (cpp != NULL && *cpp != NULL) {
      char **cpp1 = *cpp;

      while (*cpp1 != NULL) {
         FREE(*cpp1);
         cpp1++;
      }
      FREE(*cpp);
   }
}
