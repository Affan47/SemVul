EditPsi_ (MolComplexS *mol_complexSP,
	      RuntimeS *runtimeSP, ConfigS *configSP,
	      double delta_psi)
{
int			residuesN, residueI;
size_t			atomsN;
ResidueS		*residueSP;
size_t			atom_startI, atom_endI, atomI;
AtomS			*atomSP;
int			n;
static VectorS		CA_vectorS, C_vectorS;


residuesN = mol_complexSP->residuesN;


atomsN = mol_complexSP->atomsN;


for (residueI = 0; residueI < residuesN; residueI++)
	{

	residueSP = mol_complexSP->residueSP + residueI;


	atom_startI = residueSP->residue_startI;
	atom_endI   = residueSP->residue_endI;


	atomSP = mol_complexSP->atomSP + atom_startI;


	if (runtimeSP->edit_single_bondF)
		{

		if ((runtimeSP->atom1_arrayI < atom_startI) ||
		    (runtimeSP->atom1_arrayI > atom_endI)   ||
		    (runtimeSP->atom2_arrayI < atom_startI) ||
		    (runtimeSP->atom2_arrayI > atom_endI))
			{
			continue;
			}
		}


	else
		{


		if (atomSP->selectedF == 0) continue;
		}


	n = ExtractCAC_ (&CA_vectorS, &C_vectorS,
			 mol_complexSP->atomSP, atom_startI, atom_endI);
	if (n < 2) continue;


	for (atomI = atom_startI; atomI <= atom_endI; atomI++)
		{

		atomSP = mol_complexSP->atomSP + atomI;


		if (strcmp (atomSP->raw_atomS.pure_atom_nameA, "O") != 0)
			{
			continue;
			}


		RotateAtom_ (atomSP, &CA_vectorS, &C_vectorS, delta_psi);
		}


	for (atomI = atom_endI + 1; atomI < atomsN; atomI++)
		{

		atomSP = mol_complexSP->atomSP + atomI;


		RotateAtom_ (atomSP, &CA_vectorS, &C_vectorS, delta_psi);
		}
	}


DihedralAngles_ (mol_complexSP, configSP);


return 1;
}
