static_iso639_alias_convert(const char *locname)
{
  struct {
    const char *alias;
    const char *iso639;
  }
  const ALIASES[] = {
    { "byelarussian", "be" },
    { "belarussian", "be" },
    { "belarusian", "be" },
    { "byelorussian", "be" },
    { "belorussian", "be" },
    { "bulgarian", "bg" },
    { "croatian", "hr" },
    { "czech", "cs" },
    { "estonian", "et" },
    { "hungarian", "hu" },
    { "magyar", "hu" },
    { "lativan", "lt" },
    { "lettic", "lv" },
    { "lettish", "lv" },
    { "lithuanian", "lt" },
    { "polish", "pl" },
    { "russian", "ru" },
    { "slovak", "sk" },
    { "slovene", "sl" },
    { "slovenian", "sl" },
    { "ukrainian", "uk" }
  };

  size_t i;

  if (!locname)
    return NULL;

  for (i = 0; i < ELEMENTS(ALIASES); i++) {
    if (strcmp(ALIASES[i].alias, locname) == 0) {
      if (options.verbosity_level > 2)
        fprintf(stderr, "Decrypted locale alias using built-in table: %s\n",
                        ALIASES[i].iso639);

      return enca_strdup(ALIASES[i].iso639);
    }
  }

  return enca_strdup(locname);
}
