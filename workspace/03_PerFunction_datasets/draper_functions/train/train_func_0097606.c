notes_parse(int dl[], char *s)
{
  int i = 0;
  int idl = 0;

  do {
    while (s[i] == ';')
      i++;
    if (s[i]) {
      if (s[i] == '-')
        dl[idl] = 1;
      else
        dl[idl] = atoi(s + i);
      idl++;
      while ((s[i]) && (s[i] != '-') && (s[i] != ';'))
        i++;
      if (s[i] == '-') {
        dl[idl] = atoi(s + i + 1);
        if (dl[idl] == 0)
          dl[idl] = maxnotes;
      } else
        dl[idl] = dl[idl - 1];
      idl++;
      while ((s[i]) && (s[i] != ';'))
        i++;
    }
  }
  while ((s[i]) && (idl < 124));
  dl[idl] = -1;
}
