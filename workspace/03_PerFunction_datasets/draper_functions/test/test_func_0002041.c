tf_clearalldelays(void)
{
 register struct tevlst_t *telp, *last_telp;

 if (__run_state != SS_SIM) return(bad_nosimtf_err("tf_(i)clearalldelays"));
 if (__rosync_slot) return(bad_rosync_err("tf_(i)clearalldelays"));
 if (__tfrec == NULL) return(bad_notfcontext_err("tf_clearalldelays"));

 if ((telp = __tfrec->setd_telst[__inum]) == NULL) return(1);

 for (last_telp = NULL; telp != NULL; telp = telp->telnxt)
  { __tevtab[telp->tevpi].te_cancel = TRUE; last_telp = telp; }
 last_telp->telnxt = __ltevfreelst;
 __ltevfreelst = __tfrec->setd_telst[__inum];
 __tfrec->setd_telst[__inum] = NULL;
 return(1);
}
