nv84_fence_emit(struct nouveau_fence *fence)
{
	struct nouveau_channel *chan = fence->channel;
	struct nv84_fence_chan *fctx = chan->fence;
	u64 addr = chan->chid * 16;

	if (fence->sysmem)
		addr += fctx->vma_gart.offset;
	else
		addr += fctx->vma.offset;

	return fctx->base.emit32(chan, addr, fence->base.seqno);
}
