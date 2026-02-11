DeleteQueryClasses(
  void *theEnv,
  QUERY_CLASS *qlist)
  {
   QUERY_CLASS *tmp;

   while (qlist != NULL)
     {
      while (qlist->chain != NULL)
        {
         tmp = qlist->chain;
         qlist->chain = qlist->chain->chain;
         DecrementDefclassBusyCount(theEnv,(void *) tmp->cls);
         rtn_struct(theEnv,query_class,tmp);
        }
      tmp = qlist;
      qlist = qlist->nxt;
      DecrementDefclassBusyCount(theEnv,(void *) tmp->cls);
      rtn_struct(theEnv,query_class,tmp);
     }
  }
