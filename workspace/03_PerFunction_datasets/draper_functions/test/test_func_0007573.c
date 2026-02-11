static_neighbour_pbc (gamgi_slist *slist, double *shift,
double *position0, double *position1, double *radius1, int *local, int *global)
{
gamgi_atom *atom;
int id_x, id_y, id_z;


atom = GAMGI_CAST_ATOM slist->data;
position1[0] = atom->position[0] + shift[0] - position0[0];
position1[1] = atom->position[1] + shift[1] - position0[1];
position1[2] = atom->position[2] + shift[2] - position0[2];
*radius1 = atom->radius * atom->radius;
*local = atom->mark;


id_x = 0;
if (shift[0] < 0) id_x = -1;
if (shift[0] > 0) id_x = 1;

id_y = 0;
if (shift[1] < 0) id_y = -1;
if (shift[1] > 0) id_y = 1;

id_z = 0;
if (shift[2] < 0) id_z = -1;
if (shift[2] > 0) id_z = 1;

*global = 9 * id_z + 3 * id_y + id_x;
}
