getlenfract(struct feature *f)

{
  struct fract *len;
  struct note *anote;
  struct rest *arest;

  len = NULL;
  if (f->type == NOTE) {
    anote = f->item;
    len = &(anote->len);
  };
  if (f->type == REST) {
    arest = f->item;
    len = &(arest->len);
  };
  return(len);
}
