convert_latin1 (gchar * str)
{
  unsigned int flag, i;
  gchar *s, *s2, *pos;

  flag = 0;
  s = g_strdup ("(");
  for (pos = str; g_utf8_get_char (pos) != 0; pos = g_utf8_next_char (pos))
    {
      if (UCOMP(pos, "\\"))
	{
	  if (UCOMP (g_utf8_next_char (pos), " "))
	    {
	      s2 = s;
	      s = g_strdup_printf ("%s ", s2);
	      g_free (s2);
	      break;
	    }
	  for (i = 0; i < N_GREEK; i++)
	    if (strncmp (pos + 1, greek[i], greek_len[i]) == 0)
	      {
		s2 = s;
		if (prop.latex_export)
		{
		  s2 = s;
		  s = g_strdup_printf ("%s\\%.3o", s2, greek_latex[i]);
		  g_free (s2);
		}
		else
		{
		  s = g_strdup_printf ("%s)t ", s2);
		  g_free (s2);
		  s2 = s;
		  s = g_strdup_printf ("%s g(\\%.3o)t sf (", s2,
		                       greek_symbol[i]);
		  g_free (s2);
		}
		pos += greek_len[i];
		while (UCOMP (g_utf8_next_char (pos), " "))
		  pos ++;
		break;
	      }
	  for (i = 0; i < N_NATURAL; i++)
	    if (strncmp (pos + 1, natural[i], natural_len[i]) == 0)
	      {
		s2 = s;
		if (prop.latex_export)
		  s = g_strdup_printf ("%s\\%.3o", s2, natural_latex[i]);
		else
		  s = g_strdup_printf ("%s%s", s2, natural_symbol[i]);
		g_free (s2);
		pos += natural_len[i];
		while (UCOMP (g_utf8_next_char (pos), " "))
		  pos ++;
		break;
	      }
	}
      else
	{
	  s2 = s;
	  s = append_char (s2, pos);
	  g_free (s2);
	}
    }
  s2 = s;
  s = g_strdup_printf ("%s)t ", s2);
  g_free (s2);

  return (s);
}
