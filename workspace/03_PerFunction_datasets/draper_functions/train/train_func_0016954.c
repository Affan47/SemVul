tool_fortran_readCharacter(char *var, guint nb, FILE *flux,
				   GError **error, ToolFortranEndianId endianness,
				   gboolean testFlag, gboolean store)
{
  guint readNb;
  gboolean valid;

  if (testFlag)
    {

      valid = tool_fortran_readFlag(&readNb, flux, error, endianness);
      if (!valid || readNb != nb * sizeof(char))
	{
	  *error = g_error_new(VISU_ERROR_RENDERING, RENDERING_ERROR_FORMAT,
			       _("flag size unmatch, '%s' error.\n"),
			       "tool_fortran_readCharacter");
	  return FALSE;
	}
    }

  if ((store && (readNb = fread(var, sizeof(char), nb, flux)) != nb) ||
      (!store && fseek(flux, sizeof(char) * nb, SEEK_CUR) != 0))
    {
      *error = g_error_new(VISU_ERROR_RENDERING, RENDERING_ERROR_FORMAT,
			   _("impossible to read %d characters (%d read, feof: %d, ferror: %d), '%s' error.\n"),
			   nb, readNb, feof(flux), ferror(flux), "tool_fortran_readCharacter");
      return FALSE;
    }

  if (testFlag)
    {

      valid = tool_fortran_readFlag(&readNb, flux, error, endianness);
      if (!valid || readNb != nb * sizeof(char))
	{
	  *error = g_error_new(VISU_ERROR_RENDERING, RENDERING_ERROR_FORMAT,
			       _("flag size unmatch, '%s' error.\n"),
			       "tool_fortran_readCharacter");
	  return FALSE;
	}
    }
  return TRUE;
}
