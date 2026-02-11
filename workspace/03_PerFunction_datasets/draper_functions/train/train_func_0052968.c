__bld_netin_tchkterms(struct h_t *hp)
{
 register int32 hi;
 register struct hrec_t *hrp;
 int32 ndx, nterms;
 vpiHandle ihref;
 struct net_t *np;
 struct pviter_t *iterp;

 if (hp == NULL) return(__nil_iter_err(vpiTchkTerm));
 hrp = hp->hrec;
 if (hrp->htyp != vpiNet && hrp->htyp != vpiNetBit)
  {
bad_bit:
   __vpi_err(1872, vpiError,
    "vpiTchkTerm 1-to-many iterator from %s illegal - vpiNet or constant vpiNetBit only",
    __to_vpionam(__wrks1, hrp->htyp));
   return(NULL);
  }
 if (hrp->htyp == vpiNetBit)
  {
   if (!hrp->bith_ndx) goto bad_bit;
   ndx = hrp->hi;
  }
 else ndx = -1;
 np = hrp->hu.hnp;

 nterms = bld_net_tchkterms(np, (struct itree_t *) hp->hin_itp, ndx);
 if (nterms <= 0) return(NULL);

 iterp = __alloc_iter(nterms, &ihref);
 memcpy(iterp->scanhtab, __ithtab, nterms*sizeof(struct h_t));
 memcpy(iterp->ihrectab, __ithrectab, nterms*sizeof(struct hrec_t));

 for (hi = 0; hi < nterms; hi++)
  {
   iterp->scanhtab[hi].hrec = &(iterp->ihrectab[hi]);
  }
 return(ihref);
}
