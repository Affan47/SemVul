cgi_output_value(formp, name, formatstr, outstream)
     cgi_form *formp;
     char *name;
     char *formatstr;
     FILE *outstream;
{
  int i, nfound=0;

  for (i=0; i < formp->nfields; i++)
    {
      if (!strcmp(formp->fields[i].name, name))
	{
          if (!noheader)
            {
              strip_nonprint(formp->fields[i].value);
            }
	  if (nfound) fputc(' ', outstream);
	  if (formatstr)
	    {
	      if (!strcmp(formatstr, CGI_HTMLENCODE))
		cgi_string2html(formp->fields[i].value, outstream);
	      else
		{
		  if (!strcmp(formatstr, CGI_URLENCODE))
		    cgi_string2url(formp->fields[i].value, outstream);
		  else
		    fprintf(outstream, formatstr, formp->fields[i].value);
		}
	    }
	  else
	    fputs(formp->fields[i].value, outstream);
	  if (cgi_nonblank(formp->fields[i].value)) nfound++;
	}
    }
  return(nfound);
}
