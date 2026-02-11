ucs4encode(utf8 *dst, const ucs4 *s, size_t n, const char quote[128])
{
  utf8 *d = dst;
  ucs4 c;

  if (s) while (n-- > 0) {
    c = *s++;

    if (IS_UCS4_1(c)) {
      if (quote && quote[c]) {
	UTF8_S2(d, c);
	d += 2;
      }
      else {
	if (!c)
	  break;
	UTF8_S1(d, c);
	d += 1;
      }
    }
    else if (IS_UCS4_2(c)) {
      UTF8_S2(d, c);
      d += 2;
    }
    else if (IS_UCS4_3(c)) {
      UTF8_S3(d, c);
      d += 3;
    }
    else if (IS_UCS4_4(c)) {
      UTF8_S4(d, c);
      d += 4;
    }
    else if (IS_UCS4_5(c)) {
      UTF8_S5(d, c);
      d += 5;
    }
    else if (IS_UCS4_6(c)) {
      UTF8_S6(d, c);
      d += 6;
    }
    else {

    }
  }

  *d++ = 0;
  return d - dst;
}
