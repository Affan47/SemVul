convert_to_seconds (cmd_parms *cmd, const char *param, int *seconds)
{
  int num, multiplier;
  char unit;

  if (apr_isdigit(param[0])) {
    num = atoi(param);
  }
  else {
    return "Bad time string - numeric expected.";
  }

  if (*seconds < 0) *seconds = 0;
  multiplier = 1;

  unit = param[strlen(param)-1];
  if (apr_isalpha(unit)) {
    if (unit == 's')
      multiplier = 1;
    else if (unit == 'm')
      multiplier = 60;
    else if (unit == 'h')
      multiplier = 60 * 60;
    else if (unit == 'd')
      multiplier = 24 * 60 * 60;
    else if (unit == 'w')
      multiplier = 7 * 24 * 60 * 60;
    else if (unit == 'M')
      multiplier = 30 * 24 * 60 * 60;
    else if (unit == 'y')
      multiplier = 365 * 24 * 60 * 60;
    else
      return apr_psprintf(cmd->pool,
        "Bad time string - unrecognised unit '%c'", unit);
  }

  *seconds += num * multiplier;

  return NULL;
}
