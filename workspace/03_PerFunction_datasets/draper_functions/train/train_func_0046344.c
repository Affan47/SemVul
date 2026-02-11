WriteStreamHandler(cldata, netfd, xid)
XtPointer cldata;
int *netfd;
XtInputId *xid;
{
  ChimeraStream ps = (ChimeraStream)cldata;
  ssize_t wlen;
  int s;

  if (ps->bound) s = ps->as;
  else s = ps->s;

  wlen = write(s, ps->wrb + ps->wri, ps->wrmax - ps->wri);
  if (wlen < 0)
  {
    if (errno != EWOULDBLOCK)
    {
      XtRemoveInput(ps->wrid);
      ps->wrid = 0;
      CMethod(ps->wrfunc)(ps, -1, ps->wrclosure);
    }
  }
  else
  {
    ps->wri += wlen;
    if (ps->wri == ps->wrmax)
    {
      XtRemoveInput(ps->wrid);
      ps->wrid = 0;
      CMethod(ps->wrfunc)(ps, 0, ps->wrclosure);
    }
  }

  return;
}
