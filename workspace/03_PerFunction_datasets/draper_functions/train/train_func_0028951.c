static_rods_end (gamgi_rcp *rcp)
{
gamgi_rod **rods;
int n_rods;
int i;

rods = rcp->rods;
n_rods = rcp->n_atoms;

for (i = 0; i < n_rods; i++) free (rods[i]);

free (rods);
}
