wr_1subtree_allvars(struct itree_t *itp, int32 level)
{
 register int32 ii;
 struct mod_t *imdp;
 struct symtab_t *sytp;
 struct itree_t *down_itp;

 wr_1inst_dvhdrs(itp);
 imdp = itp->itip->imsym->el.emdp;

 if ((sytp = imdp->msymtab->sytofs) != NULL) wr_tasks_dvhdrs(itp, sytp);
 if (level != 1)
  {
   for (ii = 0; ii < imdp->minum; ii++)
    {
     down_itp = &(itp->in_its[ii]);
     sprintf(__xs2, "$scope module %s $end\n", down_itp->itip->isym->synam);
     __adds(__xs2);
     dv_wr(FALSE);

     wr_1subtree_allvars(down_itp, (level != 0) ? level - 1 : 0);
     sprintf(__xs2, "$upscope $end\n");
     __adds(__xs2);
     dv_wr(FALSE);
    }
  }
}
