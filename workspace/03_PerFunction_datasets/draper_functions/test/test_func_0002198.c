fsbe_begin_post_head(cx, bp)
fsbe_context *cx;
Block *bp;
{
#ifdef FSBE_DEBUG
  if (bp->post_head) {
    fsbe_printf(cx, "C *** >>> post_head\n");
  }
#endif

#if 1
  if (((bp->kind == LOOP || bp->kind == DOSUM || bp->kind == DOALL ||
	bp->kind == DOACR) && cx->last_label) &&
      (bp->pre_head->stm_head->qr_head->ope != OPE_APVLOOP)) {
    fsbe_printf(cx, "%5d CONTINUE\n", cx->last_label);
  }
#else
  if (((bp->kind == LOOP || bp->kind == DOSUM || bp->kind == DOALL ||
	bp->kind == DOACR)) &&
      (bp->pre_head->stm_head->qr_head->ope != OPE_APVLOOP)) {
    fsbe_printf(cx, "      END DO\n");
  }
#endif
}
