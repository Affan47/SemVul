reassign2_itnums(struct itree_t *new_itp)
{
 register int32 ii;
 struct itree_t *itp;
 struct mod_t *imdp, *mdp;

 imdp = new_itp->itip->imsym->el.emdp;

 for (ii = 0; ii < imdp->minum; ii++)
  {

   itp = &(new_itp->in_its[ii]);
   mdp = itp->itip->imsym->el.emdp;
   itp->itinum = (mdp->lastinum)++;
  }

 for (ii = 0; ii < imdp->minum; ii++)
  reassign2_itnums(&(new_itp->in_its[ii]));
}
