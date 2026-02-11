match_names_to_data (Char *str, pointarray treenode, node **p, long spp)
{


  boolean found;
  long i, n;

  n = 1;
  do {
    found = true;
    for (i = 0; i < nmlngth; i++) {
      found = (found && ((str[i] == nayme[n - 1][i]) ||
        (((nayme[n - 1][i] == '_') && (str[i] == ' ')) ||
        ((nayme[n - 1][i] == ' ') && (str[i] == '\0')))));
    }

    if (found)
      *p = treenode[n - 1];
    else
      n++;

  } while (!(n > spp || found));

  if (n > spp) {
    printf("\n\nERROR: Cannot find species: ");
    for (i = 0; (str[i] != '\0') && (i < MAXNCH); i++)
      putchar(str[i]);
    printf(" in data file\n\n");
    exxit(-1);
  }
}
