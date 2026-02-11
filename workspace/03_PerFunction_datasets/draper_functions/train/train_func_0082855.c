close_dbs(flist)
struct file_list *flist;
{
   struct file_list *fcur;

   fcur = flist->next_flist;
   while (fcur != NULL)
   {
      if (fcur->fdat != NULL) fclose(fcur->fdat);
      fcur = fcur->next_flist;
   }
}
