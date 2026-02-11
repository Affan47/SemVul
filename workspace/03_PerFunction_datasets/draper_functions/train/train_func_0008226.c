init_atomic_orbitals()
{
	gint i;

	AOAvailable = FALSE;
	for(i=0;i<Ncenters;i++)
	{
		GeomOrb[i].NAOrb = 0;
		GeomOrb[i].NAlphaOrb = 0;
		GeomOrb[i].NBetaOrb = 0;
		GeomOrb[i].CoefAlphaOrbitals = NULL;
		GeomOrb[i].OccAlphaOrbitals = NULL;
		GeomOrb[i].EnerAlphaOrbitals = NULL;
		GeomOrb[i].SymAlphaOrbitals = NULL;
		GeomOrb[i].CoefBetaOrbitals = NULL;
		GeomOrb[i].EnerBetaOrbitals = NULL;
		GeomOrb[i].OccBetaOrbitals = NULL;
		GeomOrb[i].SymBetaOrbitals = NULL;
	}

}
