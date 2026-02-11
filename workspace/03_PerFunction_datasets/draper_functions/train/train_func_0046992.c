Syntax()
{
  int i;

  printf("Syntax:\n\n");

  printf("%s name", PROG_NAME);
  for (i = 0; GRAPHOPTIONS[i].name != NULL; i++)
  {
    printf(" (--%s|-%c)", GRAPHOPTIONS[i].name, (char)GRAPHOPTIONS[i].val);
  }
  printf("\n");
}
