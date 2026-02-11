read_orbitals_in_nbo_file_alpha_or_beta(gchar *fileName,gint nAlpha, gint nBeta, gchar* typeOrb)
{
 	FILE *file;
 	gint i;
	gint k;
	gint j;
	gdouble **CoefOrbitals;
	gdouble *EnerOrbitals;
	gchar **SymOrbitals;
	gboolean om = FALSE;
	gdouble dum;

 	if ((!fileName) || (strcmp(fileName,"") == 0))
 	{
		Message(_("Sorry No file selected\n"),_("Error"),TRUE);
    		return FALSE;
 	}

 	file = FOpen(fileName, "rb");
 	if(file ==NULL)
 	{
		gchar buffer[BSIZE];
		sprintf(buffer,_("Sorry, I can not open '%s' file\n"),fileName);
  		Message(buffer,_("Error"),TRUE);
  		return FALSE;
 	}
	{
		gchar t[BSIZE];
    		{ char* e = fgets(t,BSIZE,file);}
    		{ char* e = fgets(t,BSIZE,file);}
		if(strstr(t," MOs ")) om = TRUE;
	}

	if(!goToLine(file,"--------")) return FALSE;
	if(!goToLine(file,typeOrb)) return FALSE;


	CoefOrbitals = CreateTable2(NOrb);
	EnerOrbitals = g_malloc(NOrb*sizeof(gdouble));
	SymOrbitals = g_malloc(NOrb*sizeof(gchar*));

	for(j=0;j<NOrb;j++)
	{
		EnerOrbitals[j]=0.0;
		for(i=0;i<NOrb;i++)
		{
			if(1!=fscanf(file,"%lf",&dum))break;
			if(om) CoefOrbitals[i][j] = dum;
			else CoefOrbitals[j][i] = dum;
		}
		if(i!=NOrb)
		{
			for(k=j;k<NOrb;k++) SymOrbitals[k] = g_strdup("DELETED");
			break;
		}
		SymOrbitals[j] = g_strdup("UNK");
	}


	if(strstr(typeOrb,"ALPHA"))
	{
	CoefAlphaOrbitals = CoefOrbitals;
	EnerAlphaOrbitals = EnerOrbitals;
	SymAlphaOrbitals = SymOrbitals;
	OccAlphaOrbitals = g_malloc(NOrb*sizeof(gdouble));
	for(i=0;i<nAlpha;i++) OccAlphaOrbitals[i] = 1.0;
	for(i=nAlpha;i<NOrb;i++) OccAlphaOrbitals[i] = 0.0;
	}
	else{
	CoefBetaOrbitals = CoefOrbitals;
	EnerBetaOrbitals = EnerOrbitals;
	OccBetaOrbitals = OccAlphaOrbitals;
	SymBetaOrbitals = SymOrbitals;
	NAlphaOcc = nAlpha;
	NBetaOcc = nBeta;
	NAlphaOrb = NOrb;
	NBetaOrb = NOrb;
	}
	setTitle(file);
 	fclose(file);

	return TRUE;
}
