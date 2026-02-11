shiftRight(ib)
iBuf *ib;
{
  int i;
  wchar *tmpbuf;
  int tmpsize, tmplen;
  int offset = ib->offset;

  tmpbuf = ib->str[ib->nseg];
  tmpsize = ib->size[ib->nseg];
  for (i = ib->nseg ; offset < i ; i--) {
    ib->str[i] = ib->str[i - 1];
    ib->size[i] = ib->size[i - 1];
    ib->len[i] = ib->len[i - 1];
  }
  ib->str[offset] = tmpbuf;
  ib->size[offset] = tmpsize;
  ib->offset++;
  ib->nseg++;
  ib->curseg++;
}
