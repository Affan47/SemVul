SetOmega_ (MolComplexS *mol_complexSP, ConfigS *configSP, double omega_new)
{
int			residuesN, residueI;
size_t			atomsN, atomI;
ResidueS		*current_residueSP;
AtomS			*first_atomSP;
size_t			current_startI, current_endI;
int			n;
static VectorS		N_vectorS, CA_vectorS;
ResidueS		*previous_residueSP;
size_t			previous_startI, previous_endI;
static VectorS		previousCA_vectorS, previousC_vectorS;
double			omega_old, delta_omega;
AtomS			*atomSP;


residuesN = mol_complexSP->residuesN;


atomsN = mol_complexSP->atomsN;


for (residueI = 1; residueI < residuesN; residueI++)
	{

	current_residueSP = mol_complexSP->residueSP + residueI;


	first_atomSP = mol_complexSP->atomSP +
		       current_residueSP->residue_startI;


	if (first_atomSP->selectedF == 0) continue;


	current_startI = current_residueSP->residue_startI;
	current_endI   = current_residueSP->residue_endI;


	n = ExtractNCA_ (&N_vectorS, &CA_vectorS,
			 mol_complexSP->atomSP, current_startI, current_endI);
	if (n < 2) continue;


	previous_residueSP = mol_complexSP->residueSP + residueI - 1;


	previous_startI = previous_residueSP->residue_startI;
	previous_endI   = previous_residueSP->residue_endI;


	n = ExtractCAC_ (&previousCA_vectorS, &previousC_vectorS,
			 mol_complexSP->atomSP,
			 previous_startI, previous_endI);
	if (n < 2) continue;


	omega_old = OmegaFromCACNCA_ (&previousCA_vectorS, &previousC_vectorS,
				      &N_vectorS, &CA_vectorS,
				      configSP);
	if (omega_old == BADDIHEDANGLE) continue;


	delta_omega = omega_new - omega_old;


	for (atomI = current_startI; atomI < atomsN; atomI++)
		{

		atomSP = mol_complexSP->atomSP + atomI;


		RotateAtom_ (atomSP,
			     &previousC_vectorS, &N_vectorS, delta_omega);
                }
	}


DihedralAngles_ (mol_complexSP, configSP);


mol_complexSP->position_changedF = 1;


return 1;
}
