allocate (char * &s, int old_size, int new_size) {
  if (old_size > new_size)
    old_size = new_size;

  if (s == NULL)
    old_size = 0;

  char *t = new char[new_size];
  core_io_memory_handler(t, "CoreIO", "allocate::out of memory error");

  int i;
  for (i = 0; i < old_size; i++)
    t[i] = s[i];

  delete[] s;
  s = t;
}
