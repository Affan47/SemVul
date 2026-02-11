createIRSpectrum(GtkWidget *parentWindow, GabEditTypeFile typeOfFile)
{
	if(typeOfFile==GABEDIT_TYPEFILE_GABEDIT) read_gabedit_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_MOLDEN) read_molden_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_MOLPRO) read_molpro_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_DALTON) read_dalton_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_GAMESS) read_gamess_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_GAMESS_ANHARMONIC) read_gamess_anharmonic_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_ORCA) read_orca_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_FIREFLY) read_gamess_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_GAUSSIAN) read_gaussian_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_GAUSSIAN_ANHARMONIC) read_gaussian_anharmonic_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_NWCHEM) read_nwchem_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_PSICODE) read_psicode_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_QCHEM) read_qchem_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_ADF) read_adf_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_MPQC) read_mpqc_file_dlg();
	if(typeOfFile==GABEDIT_TYPEFILE_TXT) read_sample_2columns_file_dlg();
}
