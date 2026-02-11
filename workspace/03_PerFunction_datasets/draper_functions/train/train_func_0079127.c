visual_2d_drawable_delete(GF_VisualManager *visual, struct _drawable *drawable)
{
	DrawableContext *ctx;

	struct _drawable_store *it = visual->prev_nodes;
	struct _drawable_store *prev = NULL;
	while (it) {
		if (it->drawable != drawable) {
			prev = it;
			it = prev->next;
			continue;
		}
		if (prev) prev->next = it->next;
		else visual->prev_nodes = it->next;
		if (!it->next) visual->last_prev_entry = prev;
		gf_free(it);
		break;
	}

	ctx = visual->context;
	while (ctx && ctx->drawable) {

		if (ctx->drawable == drawable) {
			ctx->flags = 0;
			ctx->drawable = NULL;
		}
		ctx = ctx->next;
	}
	if (drawable->flags & DRAWABLE_IS_OVERLAY) {
		visual->compositor->video_out->Blit(visual->compositor->video_out, NULL, NULL, NULL, 1);
	}
}
