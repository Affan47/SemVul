getd(struct SISTREAM *s, uint32_t *v) {
  if (s->sleft<4) {
    int nread;
    memcpy(s->buff, s->buff + s->smax - s->sleft, s->sleft);
    nread = fmap_readn(s->map, &s->buff[s->sleft], s->pos, BUFSIZ - s->sleft);
    if ((nread < 0) || ((s->sleft=s->smax=nread + s->sleft)<4)) {
      return 1;
    }
    s->pos += nread;
  }
  *v = cli_readint32(&s->buff[s->smax - s->sleft]);
  s->sleft-=4;
  return 0;
}
