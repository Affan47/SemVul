output(const Char *s, size_t n, OutputByteStream *sb)
{
  for (; n > 0; s++, n--) {
    Char c = *s;
    if (c < min2)
      sb->sputc((unsigned char)c);
    else if (c < min3) {
      sb->sputc((c >> 6) | cval2);
      sb->sputc((c & 0x3f) | 0x80);
    }
    else if (c < min4) {
      sb->sputc((c >> 12) | cval3);
      sb->sputc(((c >> 6) & 0x3f) | 0x80);
      sb->sputc((c & 0x3f) | 0x80);
    }
    else if (c < min5) {
      sb->sputc((c >> 18) | cval4);
      sb->sputc(((c >> 12) & 0x3f) | 0x80);
      sb->sputc(((c >> 6) & 0x3f) | 0x80);
      sb->sputc((c & 0x3f) | 0x80);
    }
    else if (c < min6) {
      sb->sputc((c >> 24) | cval5);
      sb->sputc(((c >> 18) & 0x3f) | 0x80);
      sb->sputc(((c >> 12) & 0x3f) | 0x80);
      sb->sputc(((c >> 6) & 0x3f) | 0x80);
      sb->sputc((c & 0x3f) | 0x80);
    }
    else if (c <= max6) {
      sb->sputc((c >> 30) | cval6);
      sb->sputc(((c >> 24) & 0x3f) | 0x80);
      sb->sputc(((c >> 18) & 0x3f) | 0x80);
      sb->sputc(((c >> 12) & 0x3f) | 0x80);
      sb->sputc(((c >> 6) & 0x3f) | 0x80);
      sb->sputc((c & 0x3f) | 0x80);
    }
  }
}
