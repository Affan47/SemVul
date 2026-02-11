findtarget(flagwild,prepend,addr)
int flagwild;
char *prepend;
char *addr;
{
  int r;
  int at;

  if (!stralloc_copys(&key,prepend)) nomem();
  if (!stralloc_cats(&key,addr)) nomem();
  case_lowerb(key.s,key.len);

  r = cdb_seek(fdcdb,key.s,key.len,&dlen);
  if (r == -1) cdbreaderror();
  if (r) return 1;

  if (!flagwild) return 0;
  at = str_rchr(addr,'@');
  if (!addr[at]) return 0;

  if (!stralloc_copys(&key,prepend)) nomem();
  if (!stralloc_cats(&key,addr + at)) nomem();
  case_lowerb(key.s,key.len);

  r = cdb_seek(fdcdb,key.s,key.len,&dlen);
  if (r == -1) cdbreaderror();
  if (r) return 1;

  if (!stralloc_copys(&key,prepend)) nomem();
  if (!stralloc_catb(&key,addr,at + 1)) nomem();
  case_lowerb(key.s,key.len);

  r = cdb_seek(fdcdb,key.s,key.len,&dlen);
  if (r == -1) cdbreaderror();
  if (r) return 1;

  return 0;
}
