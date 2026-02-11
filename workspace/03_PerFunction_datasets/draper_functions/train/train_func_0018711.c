read_mpqc_file(GabeditFileChooser *SelecFile, gint response_id)
{
	gchar *FileName;
	gint j;
	FILE* file;

	if(response_id != GTK_RESPONSE_OK) return;
 	FileName = gabedit_file_chooser_get_current_file(SelecFile);

 	file = FOpen(FileName, "rb");
	stop_vibration(NULL, NULL);
	if(!file)
	{
		gchar buffer[BSIZE];
		sprintf(buffer,_("Sorry, I can not open '%s' file\n"),FileName);
  		Message(buffer,_("Error"),TRUE);
		return;
	}
 	if(gl_read_mpqc_file_geomi(FileName,-1))
	{
		free_vibration();
		vibration.numberOfAtoms = Ncenters;
		vibration.geometry = g_malloc(Ncenters*sizeof(VibrationGeom));
		for(j=0;j<Ncenters;j++)
		{
			vibration.geometry[j].symbol = g_strdup(GeomOrb[j].Symb);
    			vibration.geometry[j].coordinates[0] = GeomOrb[j].C[0];
    			vibration.geometry[j].coordinates[1] = GeomOrb[j].C[1];
    			vibration.geometry[j].coordinates[2] = GeomOrb[j].C[2];
    			vibration.geometry[j].partialCharge = GeomOrb[j].partialCharge;
    			vibration.geometry[j].variable = GeomOrb[j].variable;
    			vibration.geometry[j].nuclearCharge = GeomOrb[j].nuclearCharge;
		}
		if(read_mpqc_modes(file,FileName))
		{
				rafreshList();
		}
	}
	fclose(file);
}
