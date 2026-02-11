signalsavelax(char *signame)
{
   lax_name_list *chain;

   if (LAX)
   {
      for (chain=LAX->intermediate; chain; chain=chain->next) {
         if ( (char*)chain->name == signame ) return 1;
      }
   }
   return 0;
}
