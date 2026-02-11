scan_peek(SCANINST si) {
  if (si->cache == -1) {
    si->cache = si->getter(si->arg);
  }

  if (si->cache == '\r')
    si->cache = '\n';

  if (si->cache == '\n')
    si->linenum++;

  return si->cache;
}
