argv_free(int *argc, char ***argv)
{
   int i;

   for (i = 0; i <= *argc; i++)
      free((*argv)[i]);

   free(*argv);
   *argc = 0;
}
