LoadDefaultPDBTpl()
{
	PDBTemplate* pdbTemplate = NULL;
	gchar* filename = g_strdup_printf("%s%sDefaultPDBTemplate.tpl",
			gabedit_directory(), G_DIR_SEPARATOR_S);

	pdbTemplate = g_malloc(sizeof(PDBTemplate));
	if(!readPDBTemplate(pdbTemplate,filename))
	{
		g_free(pdbTemplate);
		pdbTemplate = NULL;
	}

	g_free(filename);
	return pdbTemplate;
}
