gamgi_math_measure_angle_3atom (gamgi_atom *atom1,
gamgi_atom *atom2, gamgi_atom *atom3, double *angle, gamgi_layer *layer)
{
double v21[3], v23[3];
double length;


gamgi_math_vector_absolute (v21,
atom1->position[0] - atom2->position[0],
atom1->position[1] - atom2->position[1],
atom1->position[2] - atom2->position[2]);
length = gamgi_math_vector_length (v21);
if (length < GAMGI_MATH_TOLERANCE_LENGTH) return FALSE;

gamgi_math_vector_absolute (v23,
atom3->position[0] - atom2->position[0],
atom3->position[1] - atom2->position[1],
atom3->position[2] - atom2->position[2]);
length = gamgi_math_vector_length (v23);
if (length < GAMGI_MATH_TOLERANCE_LENGTH) return FALSE;


*angle = static_atom_rotation (v21, v23, layer);

return TRUE;
}
