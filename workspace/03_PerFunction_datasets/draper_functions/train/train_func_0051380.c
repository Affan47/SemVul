tf_unscale_longdelay(char *cell, int32 delay_lo, int32 delay_hi,
 int32 *aof_delay_lo, int32 *aof_delay_hi)
{
 word64 t1, t2;
 struct tfinst_t *tfi;
 struct mod_t *mdp;

 tfi = (struct tfinst_t *) cell;
 mdp = tfi->tfitp->itip->imsym->el.emdp;


 t1 = ((word64) ((word32) delay_lo)) | (((word64) ((word32) delay_hi)) << 32);

 if (!mdp->mno_unitcnv) __cnv_ticks_tonum64(&t2, t1, mdp);
 else t2 = t1;
 *aof_delay_hi = (int32) ((t2 >> 32) & WORDMASK_ULL);
 *aof_delay_lo = (int32) (t2 & WORDMASK_ULL);
}
