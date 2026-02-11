InitSlab_ (MolComplexS *mol_complexSP)
{
double		initial_extent, half_initial_extent;


mol_complexSP->slab_center_vectorS.x =
				mol_complexSP->geometric_center_vectorS.x;
mol_complexSP->slab_center_vectorS.y =
				mol_complexSP->geometric_center_vectorS.y;
mol_complexSP->slab_center_vectorS.z =
				mol_complexSP->geometric_center_vectorS.z;


initial_extent = 1.40 * mol_complexSP->max_extent;


half_initial_extent = 0.5 * initial_extent;


switch (mol_complexSP->slab_modeI)
	{

	case 0:
		break;


	case 1:
		mol_complexSP->slab_front_relative_position =
							-half_initial_extent;
		mol_complexSP->slab_back_relative_position  =
							 half_initial_extent;
		break;


	case 2:
	case 3:
	case 4:
	case 5:
		mol_complexSP->slab_front_relative_position =
							 half_initial_extent;
		mol_complexSP->slab_back_relative_position  =  0.0;
		break;


	default:
		;
	}
}
