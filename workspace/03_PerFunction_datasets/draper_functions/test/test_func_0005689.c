nv04_surface_copy_m2mf(struct gl_context *ctx,
		       struct nouveau_surface *dst,
		       struct nouveau_surface *src,
		       int dx, int dy, int sx, int sy,
		       int w, int h)
{
	struct nouveau_pushbuf_refn refs[] = {
		{ src->bo, NOUVEAU_BO_RD | NOUVEAU_BO_VRAM | NOUVEAU_BO_GART },
		{ dst->bo, NOUVEAU_BO_WR | NOUVEAU_BO_VRAM | NOUVEAU_BO_GART },
	};
	struct nouveau_pushbuf *push = context_push(ctx);
	struct nouveau_hw_state *hw = &to_nouveau_context(ctx)->hw;
	struct nv04_fifo *fifo = hw->chan->data;
	unsigned dst_offset = dst->offset + dy * dst->pitch + dx * dst->cpp;
	unsigned src_offset = src->offset + sy * src->pitch + sx * src->cpp;

	while (h) {
		int count = (h > 2047) ? 2047 : h;

		if (nouveau_pushbuf_space(push, 16, 4, 0) ||
		    nouveau_pushbuf_refn (push, refs, 2))
			return;

		BEGIN_NV04(push, NV03_M2MF(DMA_BUFFER_IN), 2);
		PUSH_RELOC(push, src->bo, 0, NOUVEAU_BO_OR, fifo->vram, fifo->gart);
		PUSH_RELOC(push, dst->bo, 0, NOUVEAU_BO_OR, fifo->vram, fifo->gart);
		BEGIN_NV04(push, NV03_M2MF(OFFSET_IN), 8);
		PUSH_RELOC(push, src->bo, src->offset, NOUVEAU_BO_LOW, 0, 0);
		PUSH_RELOC(push, dst->bo, dst->offset, NOUVEAU_BO_LOW, 0, 0);
		PUSH_DATA (push, src->pitch);
		PUSH_DATA (push, dst->pitch);
		PUSH_DATA (push, w * src->cpp);
		PUSH_DATA (push, count);
		PUSH_DATA (push, 0x0101);
		PUSH_DATA (push, 0);

		src_offset += src->pitch * count;
		dst_offset += dst->pitch * count;
		h -= count;
	}
}
