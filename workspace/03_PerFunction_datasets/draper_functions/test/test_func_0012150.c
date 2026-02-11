load_size(const CParseConfig *pCfg, u_32 *pFlags, const BitfieldInfo *pBI)
{
  unsigned size;

  if (pBI)
  {
    size = pBI->size;

    if (pCfg->unsigned_bitfields && (*pFlags & (T_SIGNED | T_UNSIGNED)) == 0)
      *pFlags |= T_UNSIGNED;
  }
  else
  {
    u_32 flags = *pFlags;

#define LOAD_SIZE(type)                                                        \
        size = pCfg->layout.type ## _size ? pCfg->layout.type ## _size         \
                                          : CTLIB_ ## type ## _SIZE

    if (flags & T_VOID)
      size = 1;
    else if (flags & T_CHAR)
    {
      LOAD_SIZE(char);
      if (pCfg->unsigned_chars && (flags & (T_SIGNED | T_UNSIGNED)) == 0)
        flags |= T_UNSIGNED;
    }
    else if ((flags & (T_LONG | T_DOUBLE)) == (T_LONG | T_DOUBLE))
      LOAD_SIZE(long_double);
    else if (flags & T_LONGLONG) LOAD_SIZE(long_long);
    else if (flags & T_FLOAT)    LOAD_SIZE(float);
    else if (flags & T_DOUBLE)   LOAD_SIZE(double);
    else if (flags & T_SHORT)    LOAD_SIZE(short);
    else if (flags & T_LONG)     LOAD_SIZE(long);
    else                         LOAD_SIZE(int);

#undef LOAD_SIZE

    *pFlags = flags;
  }

  return size;
}
