ExpressionMatches(const char *pattern, const char *string)
{
   if (pattern[0] == '/') {
      size_t length = strlen(pattern);
      if (pattern[length - 1] == '/') {
	 bool res = false;
	 regex_t preg;
	 char *regex = strdup(pattern + 1);
	 regex[length - 2] = '\0';
	 if (regcomp(&preg, regex, REG_EXTENDED | REG_ICASE) != 0) {
	    _error->Warning("Invalid regular expression: %s", regex);
	 } else if (regexec(&preg, string, 0, NULL, 0) == 0) {
	    res = true;
	 }
	 free(regex);
	 regfree(&preg);
	 return res;
      }
   }
   return fnmatch(pattern, string, FNM_CASEFOLD) == 0;
}
