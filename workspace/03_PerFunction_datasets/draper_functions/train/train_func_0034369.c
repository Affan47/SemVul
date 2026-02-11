gpx_read(void)
{
#if HAVE_LIBEXPAT
  int len;
  int done = 0;
  char* buf = (char*) xmalloc(MY_CBUF_SZ);
  int result = 0;
  int extra;

  while (!done) {
    if (fd) {


      char* badchar;
      char* semi;
      int maxentlength = 8;
      len = gbfread(buf, 1, MY_CBUF_SZ - maxentlength, fd);
      done = gbfeof(fd) || !len;
      buf[len] = '\0';
      if (len < maxentlength) {
        maxentlength = len;
      }
      badchar = buf+len-maxentlength;
      badchar = strchr(badchar, '&');
      extra = maxentlength - 1;
      while (badchar && len < MY_CBUF_SZ-1) {
        semi = strchr(badchar, ';');
        while (extra && !semi) {
          len += gbfread(buf+len, 1, 1, fd);
          buf[len]='\0';
          extra--;
          if (buf[len-1] == ';') {
            semi= buf+len-1;
          }
        }
        badchar = strchr(badchar+1, '&');
      }
      {
        char hex[]="0123456789abcdef";
        badchar = strstr(buf, "&#x");
        while (badchar) {
          int val = 0;
          char* hexit = badchar+3;
          semi = strchr(badchar, ';');
          if (semi) {
            while (*hexit && *hexit != ';') {
              char hc = isalpha(*hexit) ? tolower(*hexit) : *hexit;
              val *= 16;
              val += strchr(hex, hc)-hex;
              hexit++;
            }

            if (val < 32) {
              warning(MYNAME ": Ignoring illegal character %s;\n\tConsider emailing %s at <%s>\n\tabout illegal characters in their GPX files.\n", badchar, gpx_author?gpx_author:"(unknown author)", gpx_email?gpx_email:"(unknown email address)");
              memmove(badchar, semi+1, strlen(semi+1)+1);
              len -= (semi-badchar)+1;
              badchar--;
            }
          }
          badchar = strstr(badchar+1, "&#x");
        }
      }
      result = XML_Parse(psr, buf, len, done);
    } else if (input_string) {
      done = 0;
      result = XML_Parse(psr, input_string,
                         input_string_len, done);
      done = 1;
    } else {
      done = 1;
      result = -1;
    }
    if (!result) {
      fatal(MYNAME ": XML parse error at line %d of '%s' : %s\n",
            (int) XML_GetCurrentLineNumber(psr),
            input_fname ? input_fname : "unknown file",
            XML_ErrorString(XML_GetErrorCode(psr)));
    }
  }
  xfree(buf);
#endif
}
