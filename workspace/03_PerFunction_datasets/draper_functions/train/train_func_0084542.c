InstallMountedItem(char *host,char *mountdir)

{ char buf[CF_BUFSIZE];

strcpy (buf,host);
strcat (buf,":");
strcat (buf,mountdir);

if (IsItemIn(VMOUNTED,buf))
   {
   if (! SILENT || !WARNINGS)
      {
      if (!strstr(buf,"swap"))
         {
         snprintf(OUTPUT,CF_BUFSIZE*2,"WARNING mount item %s\n",buf);
         CfLog(cferror,OUTPUT,"");
         CfLog(cferror,"is mounted multiple times!\n","");
         }
      }
   }

AppendItem(&VMOUNTED,buf,NULL);
}
