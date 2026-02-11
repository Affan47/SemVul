mmo_writestr(const char* str)
{
  int ii, topbitset = 0;
  int len = strlen(str);


  for (ii = 0; ii < len; ii++) {
    if (str[ii] & 0x80) {
      topbitset = 1;
      break;
    }
  }


  if (mmo_version < 0x12) {
    topbitset = 0;
  }


  if (topbitset) {
    gbfputc(0xFF, fout);
    gbfputc(0xFE, fout);
    gbfputc(0xFF, fout);
    gbfputc(len, fout);
  } else if (len > 254) {
    len = len & 0x7FFF;
    gbfputc(0xFF, fout);
    gbfputint16(len, fout);
  } else {
    gbfputc(len, fout);
  }
  if (len) {
    if (topbitset) {
      int utf16val;
      int utf16len;
      for (ii=0; ii<len; ii++) {
        cet_utf8_to_ucs4(str+ii, &utf16len, &utf16val);


        gbfputint16(utf16val & 0xffff, fout);

        ii += (utf16len - 1);
      }
    } else {
      gbfwrite(str, len, 1, fout);
    }
  }
}
