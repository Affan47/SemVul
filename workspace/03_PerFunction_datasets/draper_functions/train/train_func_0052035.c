getHydrogens(gint residueNumber, gchar* pdbType, gchar** hAtoms)
{
	gint j;
	gint k;
	PDBTypeTemplate* typeTemplates =
		staticPDBTemplate->residueTemplates[residueNumber].typeTemplates;
	gint numberOfTypes = staticPDBTemplate->residueTemplates[residueNumber].numberOfTypes;
	gint nH = 0;
	for(j=0;j<numberOfTypes;j++)
	{
		if(!strcmp(pdbType,typeTemplates[j].pdbType))
		{
			for(k=j+1;k<numberOfTypes;k++)
			{
				if(!typeTemplates[k].pdbType) break;
				if(typeTemplates[k].pdbType[0]!='H') break;
				sprintf(hAtoms[nH],"%s",typeTemplates[k].pdbType);
				nH++;
				if(nH>10) break;
			}
			return nH;
		}
	}
	return nH;
}
