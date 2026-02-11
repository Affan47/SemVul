Translate_ (MolComplexS *mol_complexSP, int mol_complexesN,
		 RuntimeS *runtimeSP, ConfigS *configSP,
		 double shift, int axisID)
{
int			edit_modeI;
VectorS			shift_vectorS;
int			mol_complexI;
MolComplexS		*curr_mol_complexSP;


edit_modeI = runtimeSP->edit_modeI;


switch (axisID)
	{
	case 1:
		shift_vectorS.x = shift;
		shift_vectorS.y = 0.0;
		shift_vectorS.z = 0.0;
		break;

	case 2:
		shift_vectorS.x = 0.0;
		shift_vectorS.y = shift;
		shift_vectorS.z = 0.0;
		break;

	case 3:
		shift_vectorS.x = 0.0;
		shift_vectorS.y = 0.0;
		shift_vectorS.z = shift;
		break;

	default:
		;
		break;
	}

for (mol_complexI = 0; mol_complexI < mol_complexesN; mol_complexI++)
	{

	curr_mol_complexSP = mol_complexSP + mol_complexI;


	if (curr_mol_complexSP->catchF == 0) continue;


	if ((curr_mol_complexSP->move_bits & PLANE_MASK) &&
	    (edit_modeI != 1) && (edit_modeI != 101))
		{
		TranslatePlane_ (curr_mol_complexSP, &shift_vectorS);
		}


	if ((curr_mol_complexSP->move_bits & MEMBRANE_MASK) &&
	    (edit_modeI != 1) && (edit_modeI != 101))
		{
		TranslateMembrane_ (curr_mol_complexSP, &shift_vectorS);
		}


	if (!(curr_mol_complexSP->move_bits & STRUCTURE_MASK)) continue;


	if (edit_modeI == 101)
		{

		ResizeComplex_ (curr_mol_complexSP, shift, axisID, configSP);


		continue;
		}


	TranslateComplex_ (curr_mol_complexSP,
			   &shift_vectorS, configSP, edit_modeI);
	}
}
