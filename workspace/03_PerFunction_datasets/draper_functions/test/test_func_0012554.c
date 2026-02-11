open_dbs(flist)
struct files_list *flist;
{
   struct files_list *fcur;

   fcur = flist->next;
   while (fcur != NULL)
   {
      if ( (fcur->fdat=fopen(fcur->datname, "r")) == NULL)
      {
         printf("\nBLKPROB: Cannot open blocks file %s", fcur->datname);
      }
      else
      {
         fcur->prevdat = ftell(fcur->fdat);
         printf("Database=%s\n", fcur->datname);
      }
      fcur = fcur->next;
   }
}
