DisulfideBonds_ (MolComplexS *mol_complexSP,
			int mol_complexI, ConfigS *configSP)
{
size_t		total_bondsN = 0;
int		styleI;
size_t		atomsN, atom1I, atom2I;

AtomS		*atom1SP, *atom2SP;
int		pairID;
int		bond_typeI;
double		distance;
char		alt_location1, alt_location2;


styleI = 1;


atomsN = mol_complexSP->atomsN;
if (atomsN == 0) return 0;


bond_typeI = 2;


for (atom1I = 0; atom1I < atomsN; atom1I++)
	{

	atom1SP = mol_complexSP->atomSP + atom1I;


	if (strcmp (atom1SP->raw_atomS.chemical_symbolA, " S") != 0) continue;


	for (atom2I = 0; atom2I < atomsN; atom2I++)
		{

		if (atom2I == atom1I) continue;


		atom2SP = mol_complexSP->atomSP + atom2I;


		if (strcmp (atom1SP->raw_atomS.chemical_symbolA, " S") != 0)
			continue;
		if (strcmp (atom2SP->raw_atomS.chemical_symbolA, " S") != 0)
			continue;


		pairID = CheckDistance_ (&distance,
					 atom1SP, atom2SP, configSP);


		if (pairID <= 0) continue;


		alt_location1 = atom1SP->raw_atomS.alt_location;
		alt_location2 = atom2SP->raw_atomS.alt_location;
		if ((alt_location1 != alt_location2) &&
		    (alt_location1 != ' ') && (alt_location2 != ' '))
			{
			continue;
			}


		AddBond_ (atom1SP,
			  pairID, bond_typeI,
			  mol_complexI, atom2I,
			  distance, styleI);


		total_bondsN++;
		}
	}


return total_bondsN;
}
