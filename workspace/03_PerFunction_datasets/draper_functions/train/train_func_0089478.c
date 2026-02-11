lis_list(flis, ids)
FILE *flis;
struct db_id *ids;
{
   struct db_id *id;
   int nlis;

   nlis = 0;
   id = ids->next;
   while (id != NULL)
   {
       nlis += 1;
       fprintf(flis, "%-20s", id->full_entry);
       if (strlen(id->ps)) fprintf(flis, "  PS=%s", id->ps);
       if (id->len > 0 ) fprintf(flis, "  LENGTH=%-6d", id->len);
       if (id->frag)     fprintf(flis, "  FRAGMENT");
       if (id->lst)      fprintf(flis, "  LST");
       if (strlen(id->pir)) fprintf(flis, " PIR=%s", id->pir);
       fprintf(flis, "\n");
       id = id->next;
   }
   return(nlis);
}
