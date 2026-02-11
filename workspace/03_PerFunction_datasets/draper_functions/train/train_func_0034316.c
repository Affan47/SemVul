free_pending_move(struct send_ctx *sctx, struct pending_dir_move *m)
{
	if (!list_empty(&m->list))
		list_del(&m->list);
	if (!RB_EMPTY_NODE(&m->node))
		rb_erase(&m->node, &sctx->pending_dir_moves);
	__free_recorded_refs(&m->update_refs);
	kfree(m);
}
