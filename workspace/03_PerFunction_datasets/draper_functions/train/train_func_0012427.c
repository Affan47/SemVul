com_history(char* arg __attribute__((__unused__)))
{
   HIST_ENTRY *he;


   while (next_history())
      ;

   for (he = current_history(); he != NULL; he = previous_history()) {

      printf("%s\n", he->line);
   }

   return 0;
}
