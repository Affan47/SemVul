envstr_find(const struct str* env, const char* var, long len)
{
  striter i;
  striter_loop(&i, env, 0) {
    if (memcmp(i.startptr, var, len) == 0
	&& i.startptr[len] == '=')
      return i.startptr;
  }
  return 0;
}
