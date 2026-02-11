NewPersistentContext(char *name,unsigned int ttl_minutes,enum statepolicy policy)

{ int errno;
  CF_DB *dbp;
  struct CfState state;
  time_t now = time(NULL);
  char filename[CF_BUFSIZE];

snprintf(filename,CF_BUFSIZE,"%s/state/%s",CFWORKDIR,CF_STATEDB_FILE);
MapName(filename);

if (!OpenDB(filename,&dbp))
   {
   return;
   }

cf_chmod(filename,0644);

if (ReadDB(dbp,name,&state,sizeof(state)))
   {
   if (state.policy == cfpreserve)
      {
      if (now < state.expires)
         {
         CfOut(cf_verbose,""," -> Persisent state %s is already in a preserved state --  %d minutes to go\n",name,(state.expires-now)/60);
         CloseDB(dbp);
         return;
         }
      }
   }
else
   {
   CfOut(cf_verbose,""," -> New persistent state %s\n",name);
   state.expires = now + ttl_minutes * 60;
   state.policy = policy;
   }

WriteDB(dbp,name,&state,sizeof(state));
CloseDB(dbp);
}
