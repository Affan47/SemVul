__get_gref_giarr_ip(struct gref_t *grp, int32 gri,
 struct itree_t *itp)
{
 int32 indx, ii2, ii3;
 byte *bp1, *bp2;
 struct sy_t *syp;
 struct xstk_t *xsp;
 struct giarr_t *giap;
 struct inst_t *ip;
 struct mod_t *imdp;

 syp = grp->grcmps[gri];

 if (!syp->sy_giabase) __arg_terr(__FILE__, __LINE__);

 __push_itstk(itp);


 xsp = __eval_xpr(grp->grxcmps[gri]);
 indx = (int32) xsp->ap[0];
 __pop_xstk();
 __pop_itstk();
 imdp = itp->itip->imsym->el.emdp;

 ip = syp->el.eip;
 bp1 = (byte *) ip;
 bp2 = (byte *) imdp->minsts;
 ii2 = (bp1 - bp2)/sizeof(struct inst_t);
 giap = imdp->miarr[ii2];
 if (giap->gia1 > giap->gia2)
  {
   if (indx > giap->gia1 || indx < giap->gia2) goto bad_ref;
   else ii3 = giap->gia_bi + (giap->gia1 - indx);
  }
 else
  {
   if (indx < giap->gia1 || indx > giap->gia2) goto bad_ref;
   ii3 = giap->gia_bi + (indx - giap->gia1);
  }
done:
 ip = &(imdp->minsts[ii3]);
 return(ip);

bad_ref:
 __gferr(680, grp->grfnam_ind, grp->grflin_cnt,
  "hierarchical reference %s of %s index %d (comp. %d) out of range [%d:%d]",
  grp->gnam, syp->synam, indx, gri + 1, giap->gia1, giap->gia2);
 ii3 = giap->gia_bi;
 goto done;
}
