OpenDatabase(int create)

{ int flags;

if(create)
   {
   flags = DB_CREATE|DB_EXCL;
   }
else
   {
   flags = 0;
   }

if ((errno = db_create(&dbp, NULL, 0)) != 0)
   {
   snprintf(OUTPUT, CF_BUFSIZE, "Couldn't create database handle\n");
   fprintf(stderr, "db_create: %s\n", strerror(errno));
   fprintf(stderr, OUTPUT);
   return -1;
  }

#ifdef CF_OLD_DB
if ((errno = (dbp->open)(dbp, AVDB, NULL, DB_BTREE, flags, 0644)) != 0)
#else
if ((errno = (dbp->open)(dbp, NULL, AVDB, NULL, DB_BTREE, flags, 0644)) != 0)
#endif
   {
   snprintf(OUTPUT, CF_BUFSIZE, "Couldn't open average database %s\n", AVDB);
   fprintf(stderr, "db_open: %s\n", strerror(errno));
   fprintf(stderr, OUTPUT);
   return -1;
   }

Verbose("Opened database\n");
return 0;
}
