static_ranges_remove (gamgi_rod *rod, gamgi_rcp *rcp)
{
gamgi_rod **rods;
gamgi_atom *atom1, *atom2;
gamgi_slist **ranges;
gamgi_slist *slist, *before;
int n_atoms;
int index;

rods = rcp->rods;
ranges = rcp->ranges;
n_atoms = rcp->n_atoms;

atom1= rod->central;
atom2= rod->neighbour;


before = NULL;
index = rod->range;
for (slist = ranges[index]; slist != NULL; slist = slist->next)
  {
  rod = (gamgi_rod *) slist->data;
  if (rod->central == atom1 || rod->central == atom2) break;
  before = slist;
  }


if (before == NULL) ranges[index] = slist->next;
else before->next = slist->next;

static_stock_put (slist, rcp);


rod = rods[atom1->mark];
rod->range = -1;

rod = rods[atom2->mark];
rod->range = -1;


for (index = rcp->index; index < n_atoms; index++)
  if (ranges[index] != NULL) { rcp->index = index; return; }
rcp->index = INT_MAX;
}
