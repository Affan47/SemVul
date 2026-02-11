solo_thread_try(struct solo_dev *solo_dev)
{
	struct solo_vb2_buf *vb;


	for (;;) {
		unsigned int cur_write;

		cur_write = SOLO_VI_STATUS0_PAGE(
			solo_reg_read(solo_dev, SOLO_VI_STATUS0));
		if (cur_write == solo_dev->old_write)
			return;

		spin_lock(&solo_dev->slock);

		if (list_empty(&solo_dev->vidq_active))
			break;

		vb = list_first_entry(&solo_dev->vidq_active, struct solo_vb2_buf,
				      list);

		solo_dev->old_write = cur_write;
		list_del(&vb->list);

		spin_unlock(&solo_dev->slock);

		solo_fillbuf(solo_dev, &vb->vb.vb2_buf);
	}

	assert_spin_locked(&solo_dev->slock);
	spin_unlock(&solo_dev->slock);
}
