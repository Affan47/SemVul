copyScfParameters(MolcasScf* newCopy, MolcasScf* toCopy)
{
	gint i;

	sprintf( newCopy->title,"%s", toCopy->title);
	sprintf( newCopy->type, "%s", toCopy->type);
	sprintf( newCopy->method, "%s", toCopy->method);

	newCopy->typeOfOcupations = toCopy->typeOfOcupations;

	for(i = 0; i<2; i++) newCopy->charge[i] = toCopy->charge[i];

	for(i = 0; i<2; i++) newCopy->aufBau[i] = toCopy->aufBau[i];

	for(i = 0; i<8; i++) newCopy->numberOfOccupedOrbitals[i] = -1;
	for(i = 0; i<8; i++) newCopy->numberOfOccupedOrbitalsBeta[i] = -1;

	newCopy->numberOfOrbitals = toCopy->numberOfOrbitals;
	newCopy->numberOfOrbitalsBeta = toCopy->numberOfOrbitalsBeta;
	if(newCopy->occupationOrbitals) g_free(newCopy->occupationOrbitals);
	if(newCopy->occupationOrbitalsBeta) g_free(newCopy->occupationOrbitalsBeta);

	if(toCopy->numberOfOrbitals>0)
		newCopy->occupationOrbitals  = g_malloc(toCopy->numberOfOrbitals*sizeof(gdouble));
	for(i = 0; i<toCopy->numberOfOrbitals; i++)
		newCopy->occupationOrbitals[i] = toCopy->occupationOrbitals[i];

	if(toCopy->numberOfOrbitalsBeta>0)
		newCopy->occupationOrbitalsBeta  = g_malloc(toCopy->numberOfOrbitalsBeta*sizeof(gdouble));
	for(i = 0; i<toCopy->numberOfOrbitalsBeta; i++)
		newCopy->occupationOrbitalsBeta[i] = toCopy->occupationOrbitalsBeta[i];

	newCopy->zSpin = toCopy->zSpin;

	newCopy->guessOrbitalsCore = toCopy->guessOrbitalsCore;


	newCopy->numberOfNDDOIterations = toCopy->numberOfNDDOIterations;
	newCopy->numberOfRHFIterations = toCopy->numberOfRHFIterations;

	for(i=0;i<4;i++)
		newCopy-> convergenceThresholds [i] = toCopy->convergenceThresholds[i];

	for(i=0;i<2;i++)
		newCopy->diskSize[i] = toCopy->diskSize[i];

	newCopy->ivo = toCopy->ivo;
}
