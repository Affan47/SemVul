ComplexExtent_ (MolComplexS *mol_complexSP)
{
size_t		atomI, atomsN;
AtomS		*curr_atomSP;
double		x_min, x_max, y_min, y_max, z_min, z_max;
double		x, y, z;
double		x_extent, y_extent, z_extent, max_extent;


mol_complexSP->left_top_near_vectorS.x    = 0.0;
mol_complexSP->left_top_near_vectorS.y    = 0.0;
mol_complexSP->left_top_near_vectorS.z    = 0.0;
mol_complexSP->right_bottom_far_vectorS.x = 0.0;
mol_complexSP->right_bottom_far_vectorS.y = 0.0;
mol_complexSP->right_bottom_far_vectorS.z = 0.0;


atomsN = mol_complexSP->atomsN;
if (atomsN == 0) return 0;


x_min = mol_complexSP->atomSP->raw_atomS.x[0];
x_max = x_min;
y_min = mol_complexSP->atomSP->raw_atomS.y;
y_max = y_min;
z_min = mol_complexSP->atomSP->raw_atomS.z[0];
z_max = z_min;


for (atomI = 1; atomI < atomsN; atomI++)
	{

	curr_atomSP = mol_complexSP->atomSP + atomI;


	x = curr_atomSP->raw_atomS.x[0];
	y = curr_atomSP->raw_atomS.y;
	z = curr_atomSP->raw_atomS.z[0];
	if (x < x_min) x_min = x;
	if (y < y_min) y_min = y;
	if (z < z_min) z_min = z;
	if (x > x_max) x_max = x;
	if (y > y_max) y_max = y;
	if (z > z_max) z_max = z;
	}


if (x_max - x_min < 5.0)
	{
	x_min = -2.5;
	x_max =  2.5;
	}
if (y_max - y_min < 5.0)
	{
	y_min = -2.5;
	y_max =  2.5;
	}
if (z_max - z_min < 5.0)
	{
	z_min = -2.5;
	z_max =  2.5;
	}


mol_complexSP->left_top_near_vectorS.x    = x_min;
mol_complexSP->left_top_near_vectorS.y    = y_min;
mol_complexSP->left_top_near_vectorS.z    = z_min;
mol_complexSP->right_bottom_far_vectorS.x = x_max;
mol_complexSP->right_bottom_far_vectorS.y = y_max;
mol_complexSP->right_bottom_far_vectorS.z = z_max;


x_extent = mol_complexSP->right_bottom_far_vectorS.x -
	   mol_complexSP->left_top_near_vectorS.x;
y_extent = mol_complexSP->right_bottom_far_vectorS.y -
	   mol_complexSP->left_top_near_vectorS.y;
z_extent = mol_complexSP->right_bottom_far_vectorS.z -
	   mol_complexSP->left_top_near_vectorS.z;


max_extent = x_extent;
if (y_extent > max_extent) max_extent = y_extent;
if (z_extent > max_extent) max_extent = z_extent;
mol_complexSP->max_extent = max_extent;


return 1;
}
