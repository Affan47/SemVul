clear(SMolecule* mol)
{
	GList* l = NULL;
	for( l = mol->listOfAtoms; l != NULL;  l = l->next) if( l->data) g_free(l->data);
	g_list_free(mol->listOfAtoms);
	mol->listOfAtoms = NULL;
	mol->nAtoms = 0;
}
