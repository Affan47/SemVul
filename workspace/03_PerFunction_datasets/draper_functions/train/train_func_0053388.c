nf_parse_prefix(char *input, unsigned char mode)
{
  size_t i = 0;
  char *pnt;

  if (mode == NF_OPT_PREFIX_KTIME) {
    pnt = strchr(input, ']');
    pnt += 2;
  } else {
    pnt = input;
  }
  if (mode == NF_OPT_PREFIX || mode == NF_OPT_PREFIX_KTIME) {
    i = strlen(pnt);
    while (i > 0) {
      if (pnt[i] == '=') {
	if (pnt[i - 1] == 'N') {
	  if (pnt[i - 2] == 'I') {
	    pnt[i - 2] = '\0';
	    xstrncpy(opt.line->chainlabel, pnt, SHORTLEN);
	    xstrncpy(opt.line->interface, pnt + i + 1, SHORTLEN);
	    break;
	  }
	}
      }
      i--;
    }
  } else {
    xstrncpy(opt.line->chainlabel, "-", SHORTLEN);
    xstrncpy(opt.line->interface, pnt, SHORTLEN);
  }

  opt.parser = opt.parser | NF_IN;
}
