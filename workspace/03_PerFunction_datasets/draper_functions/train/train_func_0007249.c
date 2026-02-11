addStrings(int argc, char **argv,
					    int position)
{
  int i;
  for (i = 0; i < argc; i++)
    add(argv[i], position + i);
}
