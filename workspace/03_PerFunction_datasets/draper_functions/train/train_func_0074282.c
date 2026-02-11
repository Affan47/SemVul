free_gone_glbs(void)
{
 register int32 gri, ngri;
 register struct gref_t *grp;
 register struct mod_t *mdp;
 struct gref_t *ngrtab;
 int32 ngrnum;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mgrnum == 0) continue;
   __push_wrkitstk(mdp, 0);


   grp = &(mdp->mgrtab[0]);
   for (ngrnum = gri = 0; gri < __inst_mod->mgrnum; grp++, gri++)
    {

     if (grp->gr_err || grp->gr_gone) continue;
     ngrnum++;
    }

   if (ngrnum == __inst_mod->mgrnum) goto nxt_mod;

   if (ngrnum == 0)
    {
     __my_free((char *) __inst_mod->mgrtab,
      __inst_mod->mgrnum*sizeof(struct gref_t));
     __inst_mod->mgrtab = NULL;
     __inst_mod->mgrnum = 0;
     goto nxt_mod;
    }

   ngrtab = (struct gref_t *) __my_malloc(ngrnum*sizeof(struct gref_t));
   grp = &(mdp->mgrtab[0]);
   for (ngri = gri = 0; gri < __inst_mod->mgrnum; grp++, gri++)
    {

     if (grp->gr_err || grp->gr_gone) { __free_1glb_flds(grp); continue; }

     ngrtab[ngri] = *grp;
     ngrtab[ngri].gxndp->ru.grp = &(ngrtab[ngri]);
     ngri++;
    }
   __my_free((char *) __inst_mod->mgrtab,
    __inst_mod->mgrnum*sizeof(struct gref_t));
   __inst_mod->mgrtab = ngrtab;
   __inst_mod->mgrnum = ngrnum;

nxt_mod:
   __pop_wrkitstk();
  }
}
