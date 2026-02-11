RecFileCheck(char *startpath,void *vp)

{ struct File *ptr;
  struct stat sb;

ptr = (struct File *)vp;

Verbose("%s: Checking files in %s...\n",VPREFIX,startpath);

if (!GetLock(ASUniqueName("files"),startpath,ptr->ifelapsed,ptr->expireafter,VUQNAME,CFSTARTTIME))
   {
   return;
   }

if (stat(startpath,&sb) == -1)
   {
   snprintf(OUTPUT,CF_BUFSIZE,"Directory %s cannot be accessed in files",startpath);
   CfLog(cfinform,OUTPUT,"stat");
   ReleaseCurrentLock();
   return;
   }

CheckExistingFile("*",startpath,&sb,ptr);
RecursiveCheck(startpath,ptr->recurse,0,ptr,&sb);

ReleaseCurrentLock();
}
