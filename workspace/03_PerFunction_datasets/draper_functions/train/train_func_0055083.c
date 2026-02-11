skip_nonspaces(char **msg)
{
   char *p = *msg;

   if (!p) {
      return false;
   }
   while (*p && !B_ISSPACE(*p)) {
      p++;
   }
   *msg = p;
   return *p ? true : false;
}
