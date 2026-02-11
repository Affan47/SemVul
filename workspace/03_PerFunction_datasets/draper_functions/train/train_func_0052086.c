cool_help(int argc, char *argv[])
{
   int i;

   for(i = 1; i < argc; i++)
      if (!strcmp(argv[i], "-h"))
      {
         cool_usage();
         return(1);
      }

   return(0);
}
