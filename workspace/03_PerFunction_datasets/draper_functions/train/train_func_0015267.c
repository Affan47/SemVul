__free_flat_itree(void)
{
 register int32 ii;
 register struct mod_t *mdp;

 for (ii = 0; ii < __numtopm; ii++) free2_flat_itree(__it_roots[ii]);


 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt) mdp->lastinum = 0;
}
