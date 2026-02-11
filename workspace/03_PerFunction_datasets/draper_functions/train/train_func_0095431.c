pushbuf_flush(struct nouveau_pushbuf *push)
{
	struct nouveau_pushbuf_priv *nvpb = nouveau_pushbuf(push);
	struct nouveau_pushbuf_krec *krec = nvpb->krec;
	struct drm_nouveau_gem_pushbuf_bo *kref;
	struct nouveau_bufctx *bctx, *btmp;
	struct nouveau_bo *bo;
	int ret = 0, i;

	if (push->channel) {
		ret = pushbuf_submit(push, push->channel);
	} else {
		nouveau_pushbuf_data(push, NULL, 0, 0);
		krec->next = malloc(sizeof(*krec));
		nvpb->krec = krec->next;
	}

	kref = krec->buffer;
	for (i = 0; i < krec->nr_buffer; i++, kref++) {
		bo = (void *)(unsigned long)kref->user_priv;
		cli_kref_set(push->client, bo, NULL, NULL);
		if (push->channel)
			nouveau_bo_ref(NULL, &bo);
	}

	krec = nvpb->krec;
	krec->vram_used = 0;
	krec->gart_used = 0;
	krec->nr_buffer = 0;
	krec->nr_reloc = 0;
	krec->nr_push = 0;

	DRMLISTFOREACHENTRYSAFE(bctx, btmp, &nvpb->bctx_list, head) {
		DRMLISTJOIN(&bctx->current, &bctx->pending);
		DRMINITLISTHEAD(&bctx->current);
		DRMLISTDELINIT(&bctx->head);
	}

	return ret;
}
