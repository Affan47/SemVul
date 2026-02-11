vchan_dma_desc_free_list(struct virt_dma_chan *vc, struct list_head *head)
{
	while (!list_empty(head)) {
		struct virt_dma_desc *vd = list_first_entry(head,
			struct virt_dma_desc, node);
		list_del(&vd->node);
		dev_dbg(vc->chan.device->dev, "txd %p: freeing\n", vd);
		vc->desc_free(vd);
	}
}
