svnic_wq_free(struct vnic_wq *wq)
{
	struct vnic_dev *vdev;
	unsigned int i;

	vdev = wq->vdev;

	svnic_dev_free_desc_ring(vdev, &wq->ring);

	for (i = 0; i < VNIC_WQ_BUF_BLKS_MAX; i++) {
		kfree(wq->bufs[i]);
		wq->bufs[i] = NULL;
	}

	wq->ctrl = NULL;

}
