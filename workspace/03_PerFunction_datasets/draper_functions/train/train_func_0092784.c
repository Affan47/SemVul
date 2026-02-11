getNumberOfValenceElectrons()
{
	gint ne = 0;
	gint a;

	for(a=0;a<vibration.numberOfAtoms;a++)
	{
  		SAtomsProp Prop = prop_atom_get(vibration.geometry[a].symbol);
		ne += Prop.atomicNumber;
	}
	return ne;
}
