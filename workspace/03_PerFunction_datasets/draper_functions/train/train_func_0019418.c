bld_srted_ipins(struct inst_t *ip,
 register struct cell_pin_t *cpp, int32 pnum, struct cell_pin_t **scptab)
{
 register int32 pi;
 register struct cell_pin_t *cpp2;
 char *chp;

 for (pi = 0; pi < pnum; pi++, cpp = cpp->cpnxt)
  {
   if (cpp->pnam == NULL)
    {
     __gferr(751, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
      "%s(%s) explicit connection list but port connection %d is implicit",
      ip->isym->synam, ip->imsym->synam, pi + 1);
     return(FALSE);
    }
   scptab[pi] = cpp;
  }
 qsort((char *) scptab, (word32) pnum, sizeof(struct cell_pin_t *), cpn_cmp);


 if (pnum <= 0) return(TRUE);

 chp = scptab[0]->pnam;
 for (pi = 1; pi < pnum; pi++)
  {
   cpp2 = scptab[pi];
   if (strcmp(chp, cpp2->pnam) == 0)
    {
     __gferr(1038, cpp2->cpfnam_ind, cpp2->cplin_cnt,
      "%s(%s) explicit connection list named port %s repeated",
      ip->isym->synam, ip->imsym->synam, chp);
    }
   else chp = scptab[pi]->pnam;
  }
 return(TRUE);
}
