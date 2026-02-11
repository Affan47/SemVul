solo_v4l2_exit(struct solo_dev *solo_dev)
{
	if (solo_dev->vfd == NULL)
		return;

	video_unregister_device(solo_dev->vfd);
	vb2_dma_contig_cleanup_ctx(solo_dev->alloc_ctx);
	v4l2_ctrl_handler_free(&solo_dev->disp_hdl);
	solo_dev->vfd = NULL;
}
