cgi_string2url(instring, outstream)
     char *instring;
     FILE *outstream;
{
  while (*instring)
    {
      if (*instring == ' ')
	fputc('+', outstream);
      else
	{
	  if (isalnum(*instring) || strchr(url_safe, *instring))
	    fputc(*instring, outstream);
	  else
	    fprintf(outstream, "%%%02x", (int)*instring);
	}
      instring++;
    }
  return;
}
