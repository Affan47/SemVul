write_entry (FILE *out, const char *key, const char *value)
{
  char *v = strdup(value ? value : "");
  char *v2 = v;
  char *nl = 0;
  int col;
  Bool programs_p = (!strcmp(key, "programs"));
  int tab = (programs_p ? 32 : 16);
  Bool first = True;

  fprintf(out, "%s:", key);
  col = strlen(key) + 1;

  if (strlen(key) > 14)
    col = tab_to (out, col, 20);

  while (1)
    {
      if (!programs_p)
        v2 = strip(v2);
      nl = strchr(v2, '\n');
      if (nl)
	*nl = 0;

      if (first && programs_p)
        {
	  col = tab_to (out, col, 77);
	  fprintf (out, " \\\n");
	  col = 0;
        }

      if (first)
	first = False;
      else
	{
	  col = tab_to (out, col, 75);
	  fprintf (out, " \\n\\\n");
	  col = 0;
	}

      if (!programs_p)
        col = tab_to (out, col, tab);

      if (programs_p &&
	  string_columns(v2, strlen (v2), col) + col > 75)
	{
	  int L = strlen (v2);
	  int start = 0;
	  int end = start;
	  while (start < L)
	    {
	      while (v2[end] == ' ' || v2[end] == '\t')
		end++;
	      while (v2[end] != ' ' && v2[end] != '\t' &&
		     v2[end] != '\n' && v2[end] != 0)
		end++;
	      if (string_columns (v2 + start, (end - start), col) >= 74)
		{
		  col = tab_to (out, col, 75);
		  fprintf(out, "   \\\n");
		  col = tab_to (out, 0, tab + 2);
		  while (v2[start] == ' ' || v2[start] == '\t')
		    start++;
		}

              col = string_columns (v2 + start, (end - start), col);
	      while (start < end)
                fputc(v2[start++], out);
	    }
	}
      else
	{
	  fprintf (out, "%s", v2);
	  col += string_columns(v2, strlen (v2), col);
	}

      if (nl)
	v2 = nl + 1;
      else
	break;
    }

  fprintf(out, "\n");
  free(v);
}
