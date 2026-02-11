utils_source_filetype(GeanyFiletype *ft)
{
	if (ft)
	{
		static const filetype_id ft_id[] = { GEANY_FILETYPES_C, GEANY_FILETYPES_CPP,
			GEANY_FILETYPES_D, GEANY_FILETYPES_OBJECTIVEC, GEANY_FILETYPES_FORTRAN,
			GEANY_FILETYPES_JAVA,  GEANY_FILETYPES_PASCAL,
			 GEANY_FILETYPES_ASM,
			GEANY_FILETYPES_ADA };

		guint i;

		for (i = 0; i < sizeof ft_id / sizeof ft_id[0]; i++)
			if (ft_id[i] == ft->id)
				return TRUE;
	}

	return FALSE;
}
