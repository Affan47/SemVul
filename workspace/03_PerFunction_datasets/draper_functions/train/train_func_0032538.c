sge_is_user_superuser(const char *name)
{
   bool ret = false;

#if defined(INTERIX)
   char buffer[1000];
   char *plus_sign;

   wl_get_superuser_name(buffer, 1000);


   plus_sign = strstr(buffer, "+");
   if (plus_sign!=NULL) {
      plus_sign++;
      strcpy(buffer, plus_sign);
   }
   if ((strncmp(name, buffer, 1000) == 0) || (strcmp(name, "root") == 0)) {
      ret = true;
   }
#else
   ret = (strcmp(name, "root") == 0) ? true : false;
#endif

   return ret;
}
