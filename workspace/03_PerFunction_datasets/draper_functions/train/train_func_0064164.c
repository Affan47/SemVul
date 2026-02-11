get_bool_argument(const struct my_option *opts,
                                 const char *argument)
{
  if (!my_strcasecmp(&my_charset_latin1, argument, "true") ||
      !my_strcasecmp(&my_charset_latin1, argument, "on") ||
      !my_strcasecmp(&my_charset_latin1, argument, "1"))
    return 1;
  else if (!my_strcasecmp(&my_charset_latin1, argument, "false") ||
      !my_strcasecmp(&my_charset_latin1, argument, "off") ||
      !my_strcasecmp(&my_charset_latin1, argument, "0"))
    return 0;
  my_getopt_error_reporter(WARNING_LEVEL,
      "option '%s': boolean value '%s' wasn't recognized. Set to OFF.",
      opts->name, argument);
  return 0;
}
