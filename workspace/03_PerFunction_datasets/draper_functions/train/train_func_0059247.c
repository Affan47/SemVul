reassign_itnums(void)
{
 register int32 ii;
 register struct mod_t *flmdp;
 struct itree_t *itp;

 for (flmdp = __modhdr; flmdp != NULL; flmdp = flmdp->mnxt)
  flmdp->lastinum = 0;

 for (ii = 0; ii < __numtopm; ii++)
  {
   itp = __it_roots[ii];
   flmdp = itp->itip->imsym->el.emdp;
   itp->itinum = (flmdp->lastinum)++;
   reassign2_itnums(itp);
  }


}
