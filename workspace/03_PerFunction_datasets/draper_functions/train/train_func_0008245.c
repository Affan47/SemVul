__dmp_exprtab(struct mod_t *mdp, int32 xnum)
{
 register int32 xi;
 register struct expr_t *xp;
 int32 lxi, rxi;
 char s1[RECLEN];

 if (mdp->mexprnum == 0)
  {
   __dbg_msg("+++ module %s has no expressions +++\n", mdp->msym->synam);
   return;
  }

 if (mdp->mexprtab == NULL) __misc_terr(__FILE__, __LINE__);


 __dbg_msg("+++ module %s has %d expression nodes +++\n", mdp->msym->synam,
  mdp->mexprnum);
 __push_wrkitstk(mdp, 0);
 for (xi = 0; xi < xnum; xi++)
  {
   xp = &(mdp->mexprtab[xi]);

   if (__isleaf(xp))
    {
     __dbg_msg("EXPR %d:  leaf %s\n", xi, bld_opname(s1, xp));
    }
   else
    {
     lxi = rxi = -1;
     if (xp->lu.x != NULL) lxi = xp->lu.x - &(mdp->mexprtab[0]);
     if (xp->ru.x != NULL) rxi = xp->ru.x - &(mdp->mexprtab[0]);
     __dbg_msg("EXPR %d:  op %s left [%d] right [%d]\n", xi,
      bld_opname(s1, xp), lxi, rxi);
    }
  }
 __pop_wrkitstk();
}
