saveOneFragment(PersonalFragments* personnalFragments, FILE* file,
		gint groupeNumber, gint fragmentNumber)
{
	PersonalGroupe* personnalGroupes = personnalFragments->personnalGroupes;
	OnePersonalFragment* fragments = personnalGroupes[groupeNumber].fragments;
	Fragment f;
	gint i;

	fprintf(file,"Begin %s %s Fragment\n",
			personnalGroupes[groupeNumber].groupName,
			fragments[fragmentNumber].name
			);

	f = fragments[fragmentNumber].f;
	fprintf(file,"%d\n",f.NAtoms);
	for(i=0;i<f.NAtoms;i++)
	{
		fprintf(file,"%s %s %s %s %f %f %f %f\n",
			f.Atoms[i].Residue,
			f.Atoms[i].Symb,
			f.Atoms[i].pdbType,
			f.Atoms[i].mmType,
			f.Atoms[i].Coord[0],
			f.Atoms[i].Coord[1],
			f.Atoms[i].Coord[2],
			f.Atoms[i].Charge
			);

	}
	fprintf(file,"%d %d %d\n",f.atomToDelete,f.atomToBondTo,f.angleAtom);
	fprintf(file,"End\n");
}
