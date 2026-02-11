GeometricCenter_ (MolComplexS *mol_complexSP)
{
size_t		atomsN, i;
AtomS		*curr_atomSP;
double		x = 0.0, y = 0.0, z = 0.0, denom;

atomsN = mol_complexSP->atomsN;
if (atomsN <= 0) return 0;

curr_atomSP = mol_complexSP->atomSP;
for (i = 0; i < atomsN; i++)
	{
	x += curr_atomSP->raw_atomS.x[0];
	y += curr_atomSP->raw_atomS.y;
	z += curr_atomSP->raw_atomS.z[0];
	curr_atomSP++;
	}
denom = 1.0 / (double) atomsN;
mol_complexSP->geometric_center_vectorS.x = x * denom;
mol_complexSP->geometric_center_vectorS.y = y * denom;
mol_complexSP->geometric_center_vectorS.z = z * denom;

return 1;
}
