static_start (gamgi_dlist *atoms, gamgi_group *group,
gamgi_atom *atom, gamgi_bool global, gamgi_enum structure, double visible,
double coplanar, int element, int number, double radius)
{
static_polytope *polytope;


polytope = (static_polytope *) malloc (sizeof (static_polytope));


polytope->atoms = atoms;
polytope->group = group;
polytope->atom = atom;
polytope->global = global;
polytope->structure = structure;
polytope->visible = visible;
polytope->coplanar = coplanar;
polytope->element = element;
polytope->number = number;
polytope->max = radius;

polytope->color = TRUE;
if (polytope->group->red == -1.0)
  polytope->color = FALSE;


static_cells_create (polytope);
static_arrays_create (polytope);

return polytope;
}
