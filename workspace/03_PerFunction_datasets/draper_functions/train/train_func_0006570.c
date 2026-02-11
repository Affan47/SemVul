csv_fini(struct csv_parser *p, void (*cb1)(char *, size_t, void *), void (*cb2)(char c, void *), void *data)
{

  int quoted = p->quoted;
  int pstate = p->pstate;
  size_t spaces = p->spaces;
  size_t entry_pos = p->entry_pos;

  if (p == NULL)
    return -1;


  if (p->pstate == FIELD_BEGUN && p->quoted && p->options & CSV_STRICT && p->options & CSV_STRICT_FINI) {
    p->status = CSV_EPARSE;
    return -1;
  }

  switch (p->pstate) {
    case FIELD_MIGHT_HAVE_ENDED:
      p->entry_pos -= p->spaces + 1;
    case FIELD_NOT_BEGUN:
    case FIELD_BEGUN:
      quoted = p->quoted, pstate = p->pstate;
      spaces = p->spaces, entry_pos = p->entry_pos;
      SUBMIT_FIELD(p);
      SUBMIT_ROW(p, 0);
    case ROW_NOT_BEGUN:
      ;
  }

  p->spaces = p->quoted = p->entry_pos = p->status = 0;
  p->pstate = ROW_NOT_BEGUN;

  return 0;
}
