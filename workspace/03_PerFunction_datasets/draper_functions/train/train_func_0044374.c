__nan (const char *tagp)
{
  if (tagp[0] != '\0')
    {
      char buf[6 + strlen (tagp)];
      sprintf (buf, "NAN(%s)", tagp);
      return strtod (buf, NULL);
    }

  return NAN;
}
