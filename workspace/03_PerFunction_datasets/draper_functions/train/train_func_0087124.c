ChecksumPurge()


{ DBT key,value;
  DB *dbp;
  DBC *dbcp;
  DB_ENV *dbenv = NULL;
  int ret;
  struct stat statbuf;

if ((errno = db_create(&dbp,dbenv,0)) != 0)
   {
   snprintf(OUTPUT,CF_BUFSIZE*2,"Couldn't open checksum database %s\n",CHECKSUMDB);
   CfLog(cferror,OUTPUT,"db_open");
   return;
   }

#ifdef CF_OLD_DB
if ((errno = (dbp->open)(dbp,CHECKSUMDB,NULL,DB_BTREE,DB_CREATE,0644)) != 0)
#else
if ((errno = (dbp->open)(dbp,NULL,CHECKSUMDB,NULL,DB_BTREE,DB_CREATE,0644)) != 0)
#endif
   {
   snprintf(OUTPUT,CF_BUFSIZE*2,"Couldn't open checksum database %s\n",CHECKSUMDB);
   CfLog(cferror,OUTPUT,"db_open");
   dbp->close(dbp,0);
   return;
   }


if ((ret = dbp->cursor(dbp, NULL, &dbcp, 0)) != 0)
   {
   CfLog(cferror,"Error reading from checksum database","");
   dbp->err(dbp, ret, "DB->cursor");
   return;
   }


memset(&key,0,sizeof(key));
memset(&value,0,sizeof(value));

while (dbcp->c_get(dbcp, &key, &value, DB_NEXT) == 0)
   {
   char *obj = (char *)key.data + CF_CHKSUMKEYOFFSET;

   if (stat(obj,&statbuf) == -1)
      {
      Verbose("Purging file %s from checksum db - no longer exists\n",obj);
      snprintf(OUTPUT,CF_BUFSIZE*2,"SECURITY INFO: %s checksum for %s purged - file no longer exists!",key.data,obj);
      CfLog(cferror,OUTPUT,"");

      if ((errno = dbp->del(dbp,NULL,&key,0)) != 0)
         {
         CfLog(cferror,"","db_store");
         }
      }

   memset(&key,0,sizeof(key));
   memset(&value,0,sizeof(value));
   }

dbcp->c_close(dbcp);
dbp->close(dbp,0);
}
