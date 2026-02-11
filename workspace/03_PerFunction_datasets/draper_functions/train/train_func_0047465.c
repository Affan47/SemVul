summarize(FILE *fin, FILE *fout)
{
  set<string> names;
  int pos;
  size_t linesize = 8;
  char *line = (char *) malloc(linesize);
  for (pos=0; fautogets(&line, &linesize, fin) != NULL; pos++)
  {

    char *p;
    for (p=line; *p; ++p)
    {
      if (isspace(*p))
      {
        *p = 0;
        break;
      }
    }

    string name(line);

    names.insert(name);
  }

  set<string>::iterator it;
  for (it=names.begin(); it != names.end(); ++it)
    fprintf(fout, "%s\n", it->c_str());

  free(line);
  return 0;
}
