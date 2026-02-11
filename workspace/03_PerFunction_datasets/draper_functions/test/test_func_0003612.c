remove(ParmStr value) {
    int p1 = 0;
    while (!asc_isspace(value[p1]) && value[p1] != '\0') ++p1;
    String temp; temp.assign(value,p1);
    return StringMap::remove(temp);
  }
