readFile_is_comment(char *str, AsciiKeywordData *kw,
				    AsciiMetaData *md)
{
  gchar **tokens;
  int i;

  if (kw && !strncmp(str + 1, "keyword", 7))
    {
      tokens = g_strsplit_set(str + 9, " ,\n\t\r", -1);
      for (i = 0; tokens[i]; i++)
	if (tokens[i][0] != '\0')
	  {

	    DBG_fprintf(stderr, "Atomic ASCII: get keyword '%s'.\n", tokens[i]);
	    if (!g_ascii_strcasecmp(tokens[i], "reduced"))
	      kw->reduced = TRUE;
	    else if (!g_ascii_strcasecmp(tokens[i], "angdeg"))
	      kw->angdeg = TRUE;
	    else if (!g_ascii_strcasecmp(tokens[i], "atomic") ||
		     !g_ascii_strcasecmp(tokens[i], "atomicd0") ||
		     !g_ascii_strcasecmp(tokens[i], "bohr") ||
		     !g_ascii_strcasecmp(tokens[i], "bohrd0"))
	      kw->unit = TOOL_UNITS_BOHR;
	    else if (!g_ascii_strcasecmp(tokens[i], "angstroem") ||
		     !g_ascii_strcasecmp(tokens[i], "angstroemd0"))
	      kw->unit = TOOL_UNITS_ANGSTROEM;
	    else if (!g_ascii_strcasecmp(tokens[i], "periodic"))
	      kw->bc = VISU_BOX_PERIODIC;
	    else if (!g_ascii_strcasecmp(tokens[i], "surface"))
	      kw->bc = VISU_BOX_SURFACE_ZX;
	    else if (!g_ascii_strcasecmp(tokens[i], "surfaceXY"))
	      kw->bc = VISU_BOX_SURFACE_XY;
	    else if (!g_ascii_strcasecmp(tokens[i], "freeBC"))
	      kw->bc = VISU_BOX_FREE;
	  }
      g_strfreev(tokens);
    }
  if (md && !g_ascii_strncasecmp(str + 1, "metaData", 8))
    {
      tokens = g_strsplit_set(str + 10, " ,\n\t\r", -1);
      for (i = 0; tokens[i]; i++)
	if (tokens[i][0] != '\0')
	  {

	    DBG_fprintf(stderr, "Atomic ASCII: get meta data '%s'.\n", tokens[i]);
	    if (!g_ascii_strncasecmp(tokens[i], "qpt", 3))
	      md->nqpt += 1;
	    else if (!g_ascii_strncasecmp(tokens[i], "totalEnergy", 11))
	      md->totalEnergy = readTotalEnergy(str + 10);
	    else if (!g_ascii_strncasecmp(tokens[i], "forces", 6))
	      md->forces = TRUE;
	  }
      g_strfreev(tokens);
    }
  if(str[0] == '#' || str[0] == '!')
    return TRUE;
  str = g_strstrip(str);
  return (str[0] == '\0');
}
