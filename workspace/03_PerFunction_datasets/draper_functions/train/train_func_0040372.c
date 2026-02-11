lj_str_bufnum(char *s, cTValue *o)
{
  if (LJ_LIKELY((o->u32.hi << 1) < 0xffe00000)) {
    lua_Number n = o->n;
#if __BIONIC__
    if (tvismzero(o)) { s[0] = '-'; s[1] = '0'; return 2; }
#endif
    return (size_t)lua_number2str(s, n);
  } else if (((o->u32.hi & 0x000fffff) | o->u32.lo) != 0) {
    s[0] = 'n'; s[1] = 'a'; s[2] = 'n'; return 3;
  } else if ((o->u32.hi & 0x80000000) == 0) {
    s[0] = 'i'; s[1] = 'n'; s[2] = 'f'; return 3;
  } else {
    s[0] = '-'; s[1] = 'i'; s[2] = 'n'; s[3] = 'f'; return 4;
  }
}
