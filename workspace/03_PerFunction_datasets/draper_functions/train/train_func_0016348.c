cflstat(char *file,struct stat *buf,struct Image *ip)


{ int res;

if (ip == NULL)
   {
   return lstat(file,buf);
   }

if (strcmp(ip->server,"localhost") == 0)
   {
   res = lstat(file,buf);
   CheckForHoles(buf,ip);
   return res;
   }
else
   {

   return cf_rstat(file,buf,ip,"link");
   }
}
