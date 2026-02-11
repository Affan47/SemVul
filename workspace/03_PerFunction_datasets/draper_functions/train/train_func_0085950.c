normalize_line (const char *fname, size_t line, iconv_t cd, wchar_t *string,
		wchar_t quote_char, wchar_t escape_char)
{
  int is_quoted;
  wchar_t *rp = string;
  wchar_t *wp = string;

  if (quote_char != L'\0' && *rp == quote_char)
    {
      is_quoted = 1;
      ++rp;
    }
  else
    is_quoted = 0;

  while (*rp != L'\0')
    if (*rp == quote_char)


	break;
    else if (*rp == escape_char)
      {
	++rp;
	if (quote_char != L'\0' && *rp == quote_char)

	  *wp++ = *rp++;
	else

	  switch (*rp)
	    {
	    case L'n':
	      *wp++ = L'\n';
	      ++rp;
	      break;
	    case L't':
	      *wp++ = L'\t';
	      ++rp;
	      break;
	    case L'v':
	      *wp++ = L'\v';
	      ++rp;
	      break;
	    case L'b':
	      *wp++ = L'\b';
	      ++rp;
	      break;
	    case L'r':
	      *wp++ = L'\r';
	      ++rp;
	      break;
	    case L'f':
	      *wp++ = L'\f';
	      ++rp;
	      break;
	    case L'0' ... L'7':
	      {
		int number;
		char cbuf[2];
		char *cbufptr;
		size_t cbufin;
		wchar_t wcbuf[2];
		char *wcbufptr;
		size_t wcbufin;

		number = *rp++ - L'0';
		while (number <= (255 / 8) && *rp >= L'0' && *rp <= L'7')
		  {
		    number *= 8;
		    number += *rp++ - L'0';
		  }

		cbuf[0] = (char) number;
		cbuf[1] = '\0';
		cbufptr = cbuf;
		cbufin = 2;

		wcbufptr = (char *) wcbuf;
		wcbufin = sizeof (wcbuf);


		iconv (cd, NULL, NULL, NULL, NULL);

		iconv (cd, &cbufptr, &cbufin, &wcbufptr, &wcbufin);
		if (cbufptr != &cbuf[2] || (wchar_t *) wcbufptr != &wcbuf[2])
		  error_at_line (0, 0, fname, line,
				 gettext ("invalid escape sequence"));
		else
		  *wp++ = wcbuf[0];
	      }
	      break;
	    default:
	      if (*rp == escape_char)
		{
		  *wp++ = escape_char;
		  ++rp;
		}
	      else
		;
	      break;
	    }
      }
    else
      *wp++ = *rp++;


  if (is_quoted && *rp != quote_char)
    error_at_line (0, 0, fname, line, gettext ("unterminated message"));


  *wp = L'\0';
  return;
}
