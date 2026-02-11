IntToCString(jsint i, jsint base, char *buf, size_t bufSize)
{
    char *cp;
    jsuint u;

    u = (i < 0) ? -i : i;

    cp = buf + bufSize;
    *--cp = '\0';


    switch (base) {
    case 10:
      do {
          jsuint newu = u / 10;
          *--cp = (char)(u - newu * 10) + '0';
          u = newu;
      } while (u != 0);
      break;
    case 16:
      do {
          jsuint newu = u / 16;
          *--cp = "0123456789abcdef"[u - newu * 16];
          u = newu;
      } while (u != 0);
      break;
    default:
      JS_ASSERT(base >= 2 && base <= 36);
      do {
          jsuint newu = u / base;
          *--cp = "0123456789abcdefghijklmnopqrstuvwxyz"[u - newu * base];
          u = newu;
      } while (u != 0);
      break;
    }
    if (i < 0)
        *--cp = '-';

    JS_ASSERT(cp >= buf);
    return cp;
}
