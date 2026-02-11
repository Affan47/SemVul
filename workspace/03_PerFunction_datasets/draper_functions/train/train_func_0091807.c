operator()(ParmStr word, char * aff)
  {
    char * r = aff;
    for (const char * a = aff; *a; ++a) {
      CheckAffixRes res = lang->affix()->check_affix(word, *a);
      if (res == ValidAffix) {
        *r = *a;
        ++r;
      } else if (log) {
        const char * msg = res == InvalidAffix
          ? _("Warning: Removing invalid affix '%s' from word %s.\n")
          : _("Warning: Removing inapplicable affix '%s' from word %s.\n");
        log->printf(msg, msgconv1(*a), msgconv2(word));
      }
    }
    *r = '\0';
    return r;
  }
