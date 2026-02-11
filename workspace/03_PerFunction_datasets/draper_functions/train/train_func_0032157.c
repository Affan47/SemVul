mg_untagappearance(const void *tag)
{
  struct mgastk *astk = (struct mgastk *)tag, *pos;
  struct mgcontext *ctx = astk->tag_ctx;

  RefDecr((Ref *)astk);
  if (RefCount((Ref *)astk) > 1) {
    return;
  }

  if (!(astk->flags & MGASTK_ACTIVE)) {

    TxDelete(astk->ap.tex);
    astk->ap.tex = NULL;
    LmDeleteLights(&astk->lighting);


    if (ctx) {
      if (ctx->ap_tagged == astk) {
	ctx->ap_tagged = astk->next;
	if (ctx->ap_tagged == NULL) {
	  ctx->ap_min_tag =
	    ctx->mat_min_tag =
	    ctx->light_min_tag = -1;
	  ctx->ap_max_tag =
	    ctx->mat_max_tag =
	    ctx->light_max_tag = 0;
	}
      } else {
	for (pos = ctx->ap_tagged; pos->next != astk; pos = pos->next);
	pos->next = astk->next;
      }
    } else {
      if (astk == mgatfree) {
	mgatfree = astk->next;
      } else {
	for (pos = mgatfree; pos->next != astk; pos = pos->next);
	pos->next = astk->next;
      }
    }
    astk->tag_ctx = NULL;
    astk->next = mgafree;
    mgafree = astk;
  }

  astk->flags &= ~MGASTK_TAGGED;
}
