bld2_flat_itree(struct itree_t *new_itp)
{
 register int32 ii;
 struct inst_t *ip;
 struct itree_t *itp;
 struct mod_t *up_imdp, *imdp;

 up_imdp = new_itp->itip->imsym->el.emdp;

 if (up_imdp->minum == 0) return;


 new_itp->in_its = (struct itree_t *)
  __my_malloc(up_imdp->minum*sizeof(struct itree_t));


 for (ii = 0; ii < up_imdp->minum; ii++)
  {

   itp = &(new_itp->in_its[ii]);
   __init_itree_node(itp);
   ip = &(up_imdp->minsts[ii]);
   imdp = ip->imsym->el.emdp;
   itp->itip = ip;
   itp->up_it = new_itp;

   itp->itinum = imdp->lastinum;
   imdp->lastinum += 1;


  }

 for (ii = 0; ii < up_imdp->minum; ii++)
  bld2_flat_itree(&(new_itp->in_its[ii]));
}
