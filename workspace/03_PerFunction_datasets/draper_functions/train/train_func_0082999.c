setResiduesList(PDBTemplate* pdbTemplate, FILE* file)
{
	gint nResidue;
	gchar** t = getResiduesList(file,&nResidue);

	pdbTemplate->numberOfResidues = nResidue;
	pdbTemplate->residueTemplates = NULL;
	if(nResidue>0 && t)
	{
		gint i;
		pdbTemplate->residueTemplates = g_malloc(nResidue*sizeof(PDBResidueTemplate));
		for(i=0;i<nResidue;i++)
		{
			pdbTemplate->residueTemplates[i].residueName = g_strdup(t[i]);
			pdbTemplate->residueTemplates[i].numberOfTypes = 0;
			pdbTemplate->residueTemplates[i].typeTemplates = NULL;
			g_free(t[i]);
		}
		g_free(t);
	}
}
