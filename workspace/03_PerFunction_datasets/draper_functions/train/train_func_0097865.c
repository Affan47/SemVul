warning (no, mess)
     int no;
     char *mess;
{
  switch (no)
    {
    case 1:
      fprintf(stderr,"shape - warning: derived object not saved into derived object cache; no AtFS subdirectory\n");
      return;
    case 2:
      fprintf(stderr,"shape - warning: target `%s' not remade because of errors\n", mess);
      return;
    case 3:
      fprintf(stderr,"shape - warning: defining macros via command line may cause the rebuilding of a different system than described in confid\n");
      return;
    case 4:
      fprintf(stderr,"shape - warning: no AtFS subdirectory\n");
      return;
    case 5:
      fprintf(stderr,"shape - warning: environment variable ATFSBPSIZ = 0?\n");
      return;
    case 7:
      fprintf (stderr, "shape - warning: infinite loop: target `%s' depends on itself.\n", mess);
      return;
    default:
      fprintf (stderr, "%s.\n", mess);
      return;
    }
}
