AddToKeyDB(RSA *newkey,char *mipaddr)

{ DBT key,value;
  DB *dbp;
  char keydb[CF_MAXVARSIZE];

snprintf(keydb,CF_MAXVARSIZE,"%s/ppkeys/dynamic",CFWORKDIR);

if ((DHCPLIST != NULL) && IsFuzzyItemIn(DHCPLIST,mipaddr))
   {


   if ((errno = db_create(&dbp,NULL,0)) != 0)
      {
      sprintf(OUTPUT,"Couldn't open average database %s\n",keydb);
      CfLog(cferror,OUTPUT,"db_open");
      return;
      }

#ifdef CF_OLD_DB
   if ((errno = (dbp->open)(dbp,keydb,NULL,DB_BTREE,DB_CREATE,0644)) != 0)
#else
   if ((errno = (dbp->open)(dbp,NULL,keydb,NULL,DB_BTREE,DB_CREATE,0644)) != 0)
#endif
      {
      sprintf(OUTPUT,"Couldn't open average database %s\n",keydb);
      CfLog(cferror,OUTPUT,"db_open");
      return;
      }

   memset(&key,0,sizeof(key));
   memset(&value,0,sizeof(value));

   key.data = newkey;
   key.size = sizeof(RSA);

   value.data = mipaddr;
   value.size = strlen(mipaddr)+1;

   if ((errno = dbp->put(dbp,NULL,&key,&value,0)) != 0)
      {
      dbp->err(dbp,errno,NULL);
      }

   dbp->close(dbp,0);
   chmod(keydb,0644);
   }
}
