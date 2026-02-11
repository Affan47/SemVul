computeFrequences(VibCorrections* vibCorrections)
{
 	gint nf = vibCorrections->numberOfFrequences;
	gdouble f = vibCorrections->delta*vibCorrections->delta*AMU_TO_AU;
	gint i;
	for(i=0;i<nf;i++)
	{
		vibCorrections->calculatedFrequences[i]=sqrt(fabs((
		vibCorrections->energies[0][2*i+1]+
		vibCorrections->energies[0][2*i+2]-
		2*vibCorrections->energies[0][0])/
		(f*vibCorrections->mass[i])))*AU_TO_CM1;
	}
}
