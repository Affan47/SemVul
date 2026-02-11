parse_definition(struct line_parser *lp, struct ftfil *ftfil)
{
  char *c;
  struct ftfil_def *ftfd;

  NEXT_WORD(&lp->buf, c);

  if (!c) {
    fterr_warnx("%s line %d: Expecting name.", lp->fname, lp->lineno);
    return -1;
  }


  FT_SLIST_FOREACH(ftfd, &ftfil->defs, chain) {

    if (!strcasecmp(c, ftfd->name)) {
      fterr_warnx("%s line %d: Name (%s) previously defined.", lp->fname,
        lp->lineno, c);
      return -1;
    }

  }


  if (!(ftfd = (struct ftfil_def*)malloc(sizeof
    (struct ftfil_def)))) {
    fterr_warn("malloc()");
    return -1;
  }

  bzero(ftfd, sizeof *ftfd);
  FT_STAILQ_INIT(&ftfd->matches);

  if (!(ftfd->name = (char*)malloc(strlen(c)+1))) {
    fterr_warn("malloc()");
    free(ftfd);
    return -1;
  }

  strcpy(ftfd->name, c);

  FT_SLIST_INSERT_HEAD(&ftfil->defs, ftfd, chain);

  lp->state = PARSE_STATE_DEFINITION;
  lp->cur_def = ftfd;
  lp->cur_def_match = (void*)0L;

  return 0;

}
