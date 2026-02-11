check_transitivity(char *fname)
{
  char *s, *sb, *se;
  FILE *f;
  P_EncList enclist = NULL;
  P_EncList p_e;


  s = (char*)malloc(1024);
  if ((f = fopen(fname, "r")) == NULL) {
    fprintf(stderr, "iconvcap: cannot open %s\n", fname);
    free(s);
    return 1;
  }

  while (fgets(s, 1024, f) != NULL) {
    p_e = (P_EncList)malloc(sizeof(T_EncList));
    if (strncmp(s, "#define", 7) != 0) {
      fprintf(stderr, "iconvcap: malformed input line: %s", s);
      fclose(f);
      free(s);
      free(p_e);
      return 1;
    }
    if ((sb = strchr(s, '"')) != NULL) {
      if ((se = strrchr(s, '"')) == sb) {
        fprintf(stderr, "iconvcap: malformed input line: %s", s);
        fclose(f);
        free(s);
        free(p_e);
        return 1;
      }

      p_e->enc = strncpy((char*)malloc(se-sb), sb+1, se-sb-1);
      p_e->enc[se-sb-1] = '\0';
      p_e->next = enclist;
      enclist = p_e;
    }
  }
  fclose(f);

  if (enclist == NULL) {
    fprintf(stderr, "no valid encodings\n");
    free(s);
    return 1;
  }

  while (enclist != NULL) {
    for (p_e = enclist->next; p_e != NULL; p_e = p_e->next) {
      if (iconv_check_one(enclist->enc, p_e->enc) != 0) {
        fprintf(stderr, "iconvap: iconv_open(%s, %s) failed\n",
                enclist->enc, p_e->enc);
        free(s);
        return 1;
      }
      if (iconv_check_one(p_e->enc, enclist->enc) != 0) {
        fprintf(stderr, "iconvcap: iconv_open(%s, %s) failed\n",
                p_e->enc, enclist->enc);
        free(s);
        return 1;
      }
    }
    enclist = enclist->next;
  }

  fprintf(stderr, "iconvcap: transitivity OK\n");
  free(s);
  return 0;
}
