fparse(s)
char *s;
   {
   static char buf[MaxPath+2];
   static struct fileparts fp;
   int n;
   char *p, *q;

   #if CYGWIN
      char posix_s[_POSIX_PATH_MAX + 1];
      cygwin_conv_to_posix_path(s, posix_s);
      s = posix_s;
   #endif

   q = s;
   fp.ext = p = s + strlen(s);
   while (--p >= s) {
      if (*p == '.' && *fp.ext == '\0')
         fp.ext = p;
      else if (strchr(Prefix,*p)) {
         q = p+1;
         break;
         }
      }

   fp.dir = buf;
   n = q - s;
   strncpy(fp.dir,s,n);
   fp.dir[n] = '\0';
   fp.name = buf + n + 1;
   n = fp.ext - q;
   strncpy(fp.name,q,n);
   fp.name[n] = '\0';
   p = fp.ext;
   fp.ext = fp.name + n + 1;
   strcpy(fp.ext, p);

   return &fp;
   }
