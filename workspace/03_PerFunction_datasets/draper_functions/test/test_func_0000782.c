twiddler_rest_to_value(char *s)
{
   char *ptr;
   static char buf[64];
   int ibuf = 0, len;
   struct twiddler_f_struct *sptr;
   struct twiddler_fun_struct *fptr;


   ptr = strchr(s,'=');
   if (!ptr) return s;
   ptr++;
   while (isspace(*ptr)) ptr++;
   if (!*ptr) return s;


   if (*ptr == '"') {
      ptr++;
      while (*ptr != '"') {
         if (*ptr == '\\') {
            ptr++;
            buf[ibuf++] = twiddler_escape_sequence(ptr, &len);
            ptr += len;
         }
         else
            buf[ibuf++]=*(ptr++);
      }
      buf[ibuf]='\0';
      return strdup(buf);
   }
   if (*ptr == '\\')
      return (char *)twiddler_escape_sequence(ptr+1, &len );

   if (strlen(ptr)==1) return ((char *)((unsigned long)*ptr & 0xFF));


   for (sptr = twiddler_f; sptr->instring; sptr++)
      if (!strcmp(ptr,sptr->instring)) return sptr->outstring;


   for (fptr = twiddler_functions; fptr->name; fptr++)
      if (!strncasecmp(fptr->name,ptr,strlen(fptr->name))) {
         if (active_fun_nr == TWIDDLER_MAX_ACTIVE_FUNS) {
            gpm_report(GPM_PR_ERR,GPM_MESS_TOO_MANY_SPECIAL, option.progname,
                            TWIDDLER_MAX_ACTIVE_FUNS);
            return s;
         }
         twiddler_active_funs[active_fun_nr].fun = fptr->fun;
         twiddler_active_funs[active_fun_nr].arg=strdup(ptr+strlen(fptr->name));
         return (char *)(twiddler_active_funs + active_fun_nr++);
      }

   return s;
}
