scif_setup_qp_accept(struct scif_qp *qp, dma_addr_t *qp_offset,
			 dma_addr_t phys, int local_size,
			 struct scif_dev *scifdev)
{
	void *local_q;
	void *remote_q;
	struct scif_qp *remote_qp;
	int remote_size;
	int err = 0;

	spin_lock_init(&qp->send_lock);
	spin_lock_init(&qp->recv_lock);

	remote_qp = scif_ioremap(phys, sizeof(struct scif_qp), scifdev);
	if (!remote_qp)
		return -EIO;
	qp->remote_qp = remote_qp;
	if (qp->remote_qp->magic != SCIFEP_MAGIC) {
		err = -EIO;
		goto iounmap;
	}
	qp->remote_buf = remote_qp->local_buf;
	remote_size = qp->remote_qp->inbound_q.size;
	remote_q = scif_ioremap(qp->remote_buf, remote_size, scifdev);
	if (!remote_q) {
		err = -EIO;
		goto iounmap;
	}
	qp->remote_qp->local_write = 0;


	scif_rb_init(&qp->outbound_q,
		     &qp->local_read,
		     &qp->remote_qp->local_write,
		     remote_q,
		     get_count_order(remote_size));
	local_q = kzalloc(local_size, GFP_KERNEL);
	if (!local_q) {
		err = -ENOMEM;
		goto iounmap_1;
	}
	err = scif_map_single(&qp->local_buf, local_q, scifdev, local_size);
	if (err)
		goto kfree;
	qp->remote_qp->local_read = 0;


	scif_rb_init(&qp->inbound_q,
		     &qp->remote_qp->local_read,
		     &qp->local_write,
		     local_q, get_count_order(local_size));
	err = scif_map_single(qp_offset, qp, scifdev,
			      sizeof(struct scif_qp));
	if (err)
		goto unmap;
	qp->local_qp = *qp_offset;
	return err;
unmap:
	scif_unmap_single(qp->local_buf, scifdev, local_size);
	qp->local_buf = 0;
kfree:
	kfree(local_q);
iounmap_1:
	scif_iounmap(remote_q, remote_size, scifdev);
	qp->outbound_q.rb_base = NULL;
iounmap:
	scif_iounmap(qp->remote_qp, sizeof(struct scif_qp), scifdev);
	qp->remote_qp = NULL;
	return err;
}
