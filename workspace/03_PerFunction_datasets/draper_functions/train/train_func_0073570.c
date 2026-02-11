translate_unknown(char *w, int place, TransContext ctx)


{
  static char buf[2048];
  char *ltrans;
  MorfType morf_type;
  struct morf_xtra xtra;
  char *word_starts[64], **pws, **pwe;

  if (strchr(w, '+')) {


    return translate_lujvo(w, place);
  }

  pws = pwe = word_starts;

  morf_type = morf_scan(w, &pwe, &xtra);

  switch (morf_type) {
    case MT_BOGUS:
    case MT_BAD_UPPERCASE:
    case MT_CMAVOS:


      return NULL;
    case MT_FUIVLA4:

      return "?";
    case MT_GISMU:

      return "?";
    case MT_LUJVO:
      return translate_lujvo(w, place);
    case MT_FUIVLA3:
    case MT_FUIVLA3_CVC:
    case MT_FUIVLA3X:
    case MT_FUIVLA3X_CVC:
      {
        char *p, *q;
        int count;
        char *hyphen_pos;
        hyphen_pos = xtra.u.stage_3.hyph;
        for (p=w, q=buf; p<hyphen_pos; p++) {
          if (*p != ',') {
            *q++ = *p;
          }
        }

        for (count=0; count < 2; p++) {
          if (*p != ',') count++;
        }
        p--;

        *q = 0;
        ltrans = translate_fuivla_prefix(buf, place, ctx);
        if (ltrans) {
          strcpy(buf, ltrans);
        } else {
          strcpy(buf, "?");
        }

        strcat(buf, "-[");
        strcat(buf, p);
        strcat(buf, "]");
        return buf;
      }

    case MT_CMENE:
      return "[NAME]";
  }
  return "?";
}
