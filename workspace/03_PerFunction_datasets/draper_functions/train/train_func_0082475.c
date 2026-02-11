arg_join(char *query, int argc, const char* argv[], int size)
{
  int i;
  int offset = 0;
  for (i = 1; i < argc; ++i) {
      const char* arg = argv[i];
      const int arglen = strlen(arg);
      strncpy(query+offset, arg, arglen);
      offset += arglen;
      query[offset] = ' ';
      offset += sizeof(char);
      if (offset >= size) {
          break;
      }
  }
}
