check_if_valid(const Language & l, ParmStr word) {
    if (*word == '\0')
      return invalid_word_e(l, word, _("Empty string."));
    const char * i = word;
    if (!l.is_alpha(*i)) {
      if (!l.special(*i).begin)
        return invalid_word_e(l, word, _("The character '%s' (U+%02X) may not appear at the beginning of a word."), *i);
      else if (!l.is_alpha(*(i+1)))
        return invalid_word_e(l, word, _("The character '%s' (U+%02X) must be followed by an alphabetic character."), *i);
      else if (!*(i+1))
        return invalid_word_e(l, word, _("Does not contain any alphabetic characters."));
    }
    for (;*(i+1) != '\0'; ++i) {
      if (!l.is_alpha(*i)) {
        if (!l.special(*i).middle)
          return invalid_word_e(l, word, _("The character '%s' (U+%02X) may not appear in the middle of a word."), *i);
        else if (!l.is_alpha(*(i+1)))
          return invalid_word_e(l, word, _("The character '%s' (U+%02X) must be followed by an alphabetic character."), *i);
      }
    }
    if (!l.is_alpha(*i)) {
      if (*i == '\r')
        return invalid_word_e(l, word, _("The character '\\r' (U+0D) may not appear at the end of a word. "
                                         "This probably means means that the file is using MS-DOS EOL instead of Unix EOL."), *i);
      if (!l.special(*i).end)
        return invalid_word_e(l, word, _("The character '%s' (U+%02X) may not appear at the end of a word."), *i);
    }
    return no_err;
  }
