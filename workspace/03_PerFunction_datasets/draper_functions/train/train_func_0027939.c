main(int argc, char *argv[])
{
   char **name;
   char **val;
   int    cnt;

   if (!(localeList = getenv("HTTP_ACCEPT_LANGUAGE")))

	localeList = strdup("en");

   cnt = parse_query_string(getenv("QUERY_STRING"), &name, &val);

   locale = getLocale();

   if (find_arg(GENLIB_ARG, name, val, cnt))
      return genlib();

   return help(name, val, cnt);
}
