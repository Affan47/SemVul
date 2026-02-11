camif_prepare_dma_offset(struct camif_vp *vp)
{
	struct camif_frame *f = &vp->out_frame;

	f->dma_offset.initial = f->rect.top * f->f_width + f->rect.left;
	f->dma_offset.line = f->f_width - (f->rect.left + f->rect.width);

	pr_debug("dma_offset: initial: %d, line: %d\n",
		 f->dma_offset.initial, f->dma_offset.line);
}
