TruncateFile(char *name)

{ struct stat statbuf;
  int fd;

if (cfstat(name,&statbuf) == -1)
   {
   Debug("cfengine: didn't find %s to truncate\n",name);
   }
else
   {
   if ((fd = creat(name,000)) == -1)
      {
      CfOut(cf_error,"creat","Failed to create or truncate file %s\n",name);
      }
   else
      {
      close(fd);
      }
   }
}
