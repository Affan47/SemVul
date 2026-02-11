dt3155_irq_handler_even(int irq, void *dev_id)
{
	struct dt3155_priv *ipd = dev_id;
	struct vb2_buffer *ivb;
	dma_addr_t dma_addr;
	u32 tmp;

	tmp = ioread32(ipd->regs + INT_CSR) & (FLD_START | FLD_END_ODD);
	if (!tmp)
		return IRQ_NONE;
	if ((tmp & FLD_START) && !(tmp & FLD_END_ODD)) {
		iowrite32(FLD_START_EN | FLD_END_ODD_EN | FLD_START,
							ipd->regs + INT_CSR);
		return IRQ_HANDLED;
	}
	tmp = ioread32(ipd->regs + CSR1) & (FLD_CRPT_EVEN | FLD_CRPT_ODD);
	if (tmp) {
		iowrite32(FIFO_EN | SRST | FLD_CRPT_ODD | FLD_CRPT_EVEN |
						FLD_DN_ODD | FLD_DN_EVEN |
						CAP_CONT_EVEN | CAP_CONT_ODD,
							ipd->regs + CSR1);
		mmiowb();
	}

	spin_lock(&ipd->lock);
	if (ipd->curr_buf && !list_empty(&ipd->dmaq)) {
		v4l2_get_timestamp(&ipd->curr_buf->timestamp);
		ipd->curr_buf->sequence = ipd->sequence++;
		ipd->curr_buf->field = V4L2_FIELD_NONE;
		vb2_buffer_done(&ipd->curr_buf->vb2_buf, VB2_BUF_STATE_DONE);

		ivb = list_first_entry(&ipd->dmaq, typeof(*ivb), done_entry);
		list_del(&ivb->done_entry);
		ipd->curr_buf = to_vb2_v4l2_buffer(ivb);
		dma_addr = vb2_dma_contig_plane_dma_addr(ivb, 0);
		iowrite32(dma_addr, ipd->regs + EVEN_DMA_START);
		iowrite32(dma_addr + ipd->width, ipd->regs + ODD_DMA_START);
		iowrite32(ipd->width, ipd->regs + EVEN_DMA_STRIDE);
		iowrite32(ipd->width, ipd->regs + ODD_DMA_STRIDE);
		mmiowb();
	}


	iowrite32(FLD_START_EN | FLD_END_ODD_EN | FLD_START |
			FLD_END_EVEN | FLD_END_ODD, ipd->regs + INT_CSR);
	spin_unlock(&ipd->lock);
	return IRQ_HANDLED;
}
