streq (char *u, char *v)
{
  int diff;
  for (diff = 0; diff == 0 && u[0] != NULL_CHAR && v[0] != NULL_CHAR; u++, v++) {
    diff = ((int) TO_LOWER (u[0])) - ((int) TO_LOWER (v[0]));
  }
  return (diff);
}
