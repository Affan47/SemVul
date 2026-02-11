my_strtod(const char *str, char **end, int *error)
{
  char buf[DTOA_BUFF_SIZE];
  double res;
  DBUG_ASSERT(end != NULL && ((str != NULL && *end != NULL) ||
                              (str == NULL && *end == NULL)) &&
              error != NULL);

  res= my_strtod_int(str, end, error, buf, sizeof(buf));
  return (*error == 0) ? res : (res < 0 ? -DBL_MAX : DBL_MAX);
}
