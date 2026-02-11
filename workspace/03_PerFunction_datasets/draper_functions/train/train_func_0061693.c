wordsplit_c_quote_copy (char *dst, const char *src, int quote_hex)
{
  for (; *src; src++)
    {
      if (*src == '"')
	{
	  *dst++ = '\\';
	  *dst++ = *src;
	}
      else if (*src != '\t' && *src != '\\' && ISPRINT (*src))
	*dst++ = *src;
      else
	{
	  char tmp[4];

	  if (quote_hex)
	    {
	      snprintf (tmp, sizeof tmp, "%%%02X", *(unsigned char *) src);
	      memcpy (dst, tmp, 3);
	      dst += 3;
	    }
	  else
	    {
	      int c = wordsplit_c_quote_char (*src);
	      *dst++ = '\\';
	      if (c != -1)
		*dst++ = c;
	      else
		{
		  snprintf (tmp, sizeof tmp, "%03o", *(unsigned char *) src);
		  memcpy (dst, tmp, 3);
		  dst += 3;
		}
	    }
	}
    }
}
