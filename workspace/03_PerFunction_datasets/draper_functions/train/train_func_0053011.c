read_gaussian_file(GabeditFileChooser *SelecFile, gint response_id)
{
 	gchar t[BSIZE];
 	gchar sdum1[BSIZE];
 	gchar sdum2[BSIZE];
 	gchar sdum3[BSIZE];
 	gboolean OK;
	gint nf;
	gint i;
	gdouble freq[3] = {0,0,0};
	gdouble RamanIntensity[3] = {0,0,0};
	gint numberOfFrequencies = 0;
	gdouble* frequencies = NULL;
	gdouble* intensities = NULL;
	gchar *FileName;
 	FILE *fd;

	if(response_id != GTK_RESPONSE_OK) return FALSE;
 	FileName = gabedit_file_chooser_get_current_file(SelecFile);

 	fd = FOpen(FileName, "rb");
	if(!fd) return FALSE;

 	do
 	{
 		OK=FALSE;
 		while(!feof(fd))
		{
    			if(!feof(fd)) { char* e = fgets(t,BSIZE,fd);}

	 		if ( strstr( t,"and normal coordinates:") )
	  		{
				OK = TRUE;
				numberOfFrequencies = 0;
				break;
	  		}
		}
  		while(!feof(fd) )
  		{
    			if(!feof(fd)) { char* e = fgets(t,BSIZE,fd);}
			if(!strstr(t,"Frequencies --"))continue;
			if(this_is_a_backspace(t)) break;
			nf = sscanf(t,"%s %s %lf %lf %lf", sdum1,sdum2, &freq[0],&freq[1],&freq[2]);
			nf -=2;
			if(nf<=0 || nf>3) break;
			while(!feof(fd))
			{
    				if(!feof(fd)) { char* e = fgets(t,BSIZE,fd);}
				if(strstr(t,"Raman"))
				{
					sscanf(t,"%s %s %s %lf %lf %lf", sdum1,sdum2, sdum3, &RamanIntensity[0],&RamanIntensity[1],&RamanIntensity[2]);
					break;
				}
			}
			for(i=0;i<nf;i++)
			{
				numberOfFrequencies++;
				frequencies = g_realloc(frequencies, numberOfFrequencies*sizeof(gdouble));
				intensities = g_realloc(intensities, numberOfFrequencies*sizeof(gdouble));
				frequencies[numberOfFrequencies-1] = freq[i];
				intensities[numberOfFrequencies-1] = RamanIntensity[i];
			}
		}
 	}while(!feof(fd));

	if(numberOfFrequencies>0)
	{
		createRamanSpectrumWin(numberOfFrequencies, frequencies, intensities);
	}
	else
	{
		messageErrorFreq(FileName);
	}


	if(frequencies) g_free(frequencies);
	if(intensities) g_free(intensities);
	fclose(fd);
	return TRUE;
}
