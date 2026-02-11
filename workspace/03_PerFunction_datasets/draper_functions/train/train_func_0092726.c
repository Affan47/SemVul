CopyFileSources(char *destination,struct Attributes attr,struct Promise *pp)

{ char *source = attr.copy.source;
  char *server = pp->this_server;
  char vbuff[CF_BUFSIZE];
  struct stat ssb,dsb;
  struct timespec start;
  char eventname[CF_BUFSIZE];

Debug("CopyFileSources(%s,%s)", source, destination);

if (pp->conn != NULL && !pp->conn->authenticated)
   {
   cfPS(cf_verbose,CF_FAIL,"",pp,attr,"No authenticated source %s in files.copyfrom promise\n",source);
   return NULL;
   }

if (cf_stat(attr.copy.source,&ssb,attr,pp) == -1)
   {
   cfPS(cf_inform,CF_FAIL,"",pp,attr,"Can't stat %s in files.copyfrom promise\n",source);
   return NULL;
   }

start = BeginMeasure();

strncpy(vbuff,destination,CF_BUFSIZE-4);

if (S_ISDIR(ssb.st_mode))
   {
   AddSlash(vbuff);
   strcat(vbuff,".");
   }

if (!MakeParentDirectory(vbuff,attr.move_obstructions))
   {
   cfPS(cf_inform,CF_FAIL,"",pp,attr,"Can't make directories for %s in files.copyfrom promise\n",vbuff);
   return NULL;
   }

if (S_ISDIR(ssb.st_mode))
   {
   if (attr.copy.purge)
      {
      CfOut(cf_verbose,""," !! (Destination purging enabled)\n");
      }

   CfOut(cf_verbose,""," ->>  Entering %s\n",source);
   SetSearchDevice(&ssb,pp);
   SourceSearchAndCopy(source,destination,attr.recursion.depth,attr,pp);

   if (cfstat(destination,&dsb) != -1)
      {
      if (attr.copy.check_root)
         {
         VerifyCopiedFileAttributes(destination,&dsb,&ssb,attr,pp);
         }
      }
   }
else
   {
   VerifyCopy(source,destination,attr,pp);
   }

snprintf(eventname,CF_BUFSIZE-1,"Copy(%s:%s > %s)",server,source,destination);
EndMeasure(eventname,start);

if (attr.transaction.background)
   {
   ServerDisconnection(pp->conn);
   }
else
   {
   ServerNotBusy(pp->conn);
   }

return NULL;
}
