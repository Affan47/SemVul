__bld_mlevel_lists(void)
{
 register struct mod_t *mdp, *last_mdp;
 register int32 mlevel;


 if (__mdlevhdr == NULL)
  {
   __mdlevhdr = (struct mod_t **)
    __my_malloc((__dagmaxdist + 1)*sizeof(struct mod_t *));
  }

 for (mlevel = 0; mlevel <= __dagmaxdist; mlevel++) __mdlevhdr[mlevel] = NULL;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt) mdp->mlevnxt = NULL;

 for (mlevel = 0; mlevel <= __dagmaxdist; mlevel++)
  {
   last_mdp = NULL;
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     if (mdp->mlpcnt != mlevel) continue;
     if (last_mdp == NULL) __mdlevhdr[mlevel] = mdp;
     else last_mdp->mlevnxt = mdp;
     last_mdp = mdp;
    }
  }
}
