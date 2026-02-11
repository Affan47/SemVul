freeAMolecule(MolSymMolecule* mol)
{

	gint i;
	if(mol->numberOfAtoms>0 && mol->listOfAtoms) g_free(mol->listOfAtoms);
	mol->listOfAtoms = NULL;
	mol->numberOfAtoms = 0;
	if(mol->numberOfDifferentKindsOfAtoms>0 && mol->symbol)
	{
		for(i=0;i<mol->numberOfDifferentKindsOfAtoms;i++)
			if( mol->symbol[i]) g_free(mol->symbol[i]);
		g_free(mol->symbol);
	}
	mol->symbol = NULL;
	if(mol->numberOfDifferentKindsOfAtoms>0 && mol->numberOfAtomsOfEachType) g_free(mol->numberOfAtomsOfEachType);
	mol->numberOfAtomsOfEachType = 0;
	if(mol->numberOfDifferentKindsOfAtoms>0 && mol->masse) g_free(mol->masse);
	mol->masse = 0;
	mol->numberOfDifferentKindsOfAtoms = 0;
	return 0;
}
