parse_position(Clp_Parser *clp, const char *arg, int complain, void *thunk)
{
  char *val;
  (void)thunk;

  position_x = strtol(arg, &val, 10);
  if (*val == ',') {
    position_y = strtol(val + 1, &val, 10);
    if (*val == 0)
      return 1;
  }

  if (complain)
    return Clp_OptionError(clp, "invalid position '%s' (want 'X,Y')", arg);
  else
    return 0;
}
