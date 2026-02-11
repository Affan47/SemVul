convert_string(const clamz_config *cfg, const char *s)
{
  const unsigned char *us = (const unsigned char*) s;
  char *converted;
  int len;
  int i, j;

  len = strlen(s) + 1;
  converted = malloc(len * sizeof(char));

  if (!converted) {
    print_error("Out of memory");
    return NULL;
  }

  i = j = 0;
  while (s[i]) {
    if (j >= len - 1) {
      len *= 2;
      converted = realloc(converted, len * sizeof(char));

      if (!converted) {
	print_error("Out of memory");
	return NULL;
      }
    }

    if (us[i] & 0x80) {
      if (cfg->allowutf8) {
	converted[j++] = s[i++];
      }
      else {
	converted[j++] = '_';
	do
	  i++;
	while (((unsigned char) s[i] & 0xc0) == 0x80);
      }
    }
    else if (s[i] == '/' || iscntrl(us[i])) {
      converted[j++] = '_';
      i++;
    }
    else if (isupper(us[i]) && !cfg->allowupper) {
      converted[j++] = tolower(s[i++]);
    }
    else if (cfg->forbid_chars && strchr(cfg->forbid_chars, s[i])) {
      converted[j++] = '_';
      i++;
    }
    else {
      converted[j++] = s[i++];
    }
  }

  converted[j] = 0;

  return converted;
}
