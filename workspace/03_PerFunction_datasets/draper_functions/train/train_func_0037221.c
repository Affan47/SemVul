CfCheckAudit()

{ DB_ENV *dbenv = NULL;
  char name[CF_BUFSIZE];

snprintf(name,CF_BUFSIZE-1,"%s/%s",CFWORKDIR,CF_AUDITDB_FILE);

if (AUDIT)
   {
   if ((errno = db_create(&AUDITDBP,dbenv,0)) != 0)
      {
      snprintf(OUTPUT,CF_BUFSIZE*2,"Couldn't open performance database %s\n",name);
      CfLog(cferror,OUTPUT,"db_open");
      return;
      }

#ifdef CF_OLD_DB
   if ((errno = (AUDITDBP->open)(AUDITDBP,name,NULL,DB_BTREE,DB_CREATE,0644)) != 0)
#else
   if ((errno = (AUDITDBP->open)(AUDITDBP,NULL,name,NULL,DB_BTREE,DB_CREATE,0644)) != 0)
#endif
      {
      snprintf(OUTPUT,CF_BUFSIZE*2,"Couldn't open auditing database %s\n",name);
      CfLog(cferror,OUTPUT,"db_open");
      return;
      }

   AuditLog('y',NULL,0,"Cfagent starting",CF_NOP);
   }
}
