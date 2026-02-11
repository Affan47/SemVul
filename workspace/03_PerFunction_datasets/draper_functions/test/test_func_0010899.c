__dmp_bidchan(struct chanrec_t *chanp)
{
 register struct bidvtxlst_t *bidvtxlp;
 int32 chanid;
 char s1[RECLEN];

 chanid = chanp - __chantab;
 __dbg_msg(" *** inout channel (id=%d, type=%d, mixed_wires=%d):\n",
  chanid, chanp->chtyp, chanp->chan_diffwtyps);

 bidvtxlp = chanp->bid_vtxlp;
 for (; bidvtxlp != NULL; bidvtxlp = bidvtxlp->bidvtxnxt)
  {
   if (bidvtxlp->vi1 == -1) strcpy(s1, bidvtxlp->vnp->nsym->synam);
   else sprintf(s1, "%s[%d]", bidvtxlp->vnp->nsym->synam, bidvtxlp->vi1);
   __dbg_msg(" -- vertex %s.%s\n", __msg2_blditree(__xs,
    bidvtxlp->bidvtx_itp), s1);
  }
 __dbg_msg("=== end of channel ===\n");
}
