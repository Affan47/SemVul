file_getDirOfPath(char *path)
{
   char *dir=NULL;
   char *pos;

   BEGINMESSAGE(file_getDirOfPath)

   if (path) {
      dir=XtNewString(path);
      pos = strrchr(dir,'/');
      if (pos) { pos++; *pos='\0'; }
   }

#ifdef MESSAGES
   if (!dir) { INFMESSAGE (### Warning: returning NULL) }
   else      { INFSMESSAGE(returning, dir) }
#endif
   ENDMESSAGE(file_getDirOfPath)
   return(dir);
}
