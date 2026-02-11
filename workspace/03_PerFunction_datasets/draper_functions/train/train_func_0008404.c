CleanAtomType(char *id)
  {
    id[0] = toupper(id[0]);
    if (isalpha(id[1]) == 0)
      id[1] = '\0';
    else
      {
        id[1] = tolower(id[1]);
        id[2] = '\0';
      }
  }
