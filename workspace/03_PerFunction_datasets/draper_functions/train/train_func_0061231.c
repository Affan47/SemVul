check_tp(id, tps)
char *id;
struct db_id *tps;
{
   struct db_id *did;

   did = tps->next;
   while (did != NULL)
   {
      if (strncmp(id, did->entry, strlen(did->entry)) == 0)
      {
	 did->found = YES;
         if (did->block) return(2);
         else return(YES);
      }
      did = did->next;
   }
   return(NO);
}
