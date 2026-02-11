computeSymmetry(
		gdouble principalAxisTolerance, gchar* pointGroupSymbol,
		gint maximalOrder, gboolean redu,
	       	gint* numberOfAtoms, gchar** symbols, gdouble* X, gdouble* Y, gdouble* Z,  gdouble* precision, gchar* message)
{
	gdouble eps = *precision;
	gint nAtoms = *numberOfAtoms;
	gdouble* mass = NULL;
	gint i = 0;
	SMolecule mol = newSMolecule();
	Symmetry sym;
	SMolecule* pmol = NULL;

	if(eps<=0) eps = 0.1;
	sprintf(message,"C1 Group");
	if(nAtoms<1) return 1;
	mass = g_malloc(nAtoms*sizeof(gdouble));
	for(i=0;i<nAtoms;i++) { SAtomsProp prop = prop_atom_get(symbols[i]); mass[i] =  prop.masse;}
	mol.setMolecule(&mol,  nAtoms, symbols, mass, X, Y, Z);
	sym = newSymmetry(&mol, eps);
	sym.setMaxDegree(&sym,maximalOrder);
	sym.setMomentTolerance(&sym,principalAxisTolerance);
	sym.findAllPointGroups(&sym);
	sprintf(pointGroupSymbol,"%s",sym.findSinglePointGroup(&sym));
	printf("group=%s\n",pointGroupSymbol);
       	sym.printElementResults(&sym);
	g_free(mass);
	sym.getUniqueMolecule(&sym);

	if(!strcmp(pointGroupSymbol,"C1")) return 0;

	if (redu) sym.getUniqueMolecule(&sym);

	pmol = &sym.molecule;
      	for (i=0;i < pmol->size(pmol);i++)
	{
		SAtom* atom = pmol->get(pmol,i);
		Point3D pos = atom->getPosition(atom);
		X[i] = pos.x;
		Y[i] = pos.y;
		Z[i] = pos.z;
	}
	*numberOfAtoms = pmol->size(pmol);
	sym.free(&sym);
	mol.free(&mol);

	return 0;
}
