estbd(struct conn * p)
{
  chanclose(p->estbchan);
  p->estbchan = (struct chan *) (0);
  if ((*(p->estbfunc)) (p->acb, p->fd)) {
    connackestb(p);
  }
  return;
}
