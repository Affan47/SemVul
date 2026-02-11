delsignal(char *name)
{

   if (!name) {
      fprintf(stderr,"delsignal: no name\n");
      exit(1);
   }


   if (!HTABLE) init_signals();

   delauthelem(HTABLE,name);
}
