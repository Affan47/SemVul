frame_boundary(struct go7007 *go, struct go7007_buffer *vb)
{
	u32 *bytesused;
	struct go7007_buffer *vb_tmp = NULL;

	if (vb == NULL) {
		spin_lock(&go->spinlock);
		if (!list_empty(&go->vidq_active))
			vb = go->active_buf =
				list_first_entry(&go->vidq_active, struct go7007_buffer, list);
		spin_unlock(&go->spinlock);
		go->next_seq++;
		return vb;
	}
	bytesused = &vb->vb.vb2_buf.planes[0].bytesused;

	vb->vb.sequence = go->next_seq++;
	if (vb->modet_active && *bytesused + 216 < GO7007_BUF_SIZE)
		go7007_motion_regions(go, vb);
	else
		go7007_set_motion_regions(go, vb, 0);

	v4l2_get_timestamp(&vb->vb.timestamp);
	vb_tmp = vb;
	spin_lock(&go->spinlock);
	list_del(&vb->list);
	if (list_empty(&go->vidq_active))
		vb = NULL;
	else
		vb = list_first_entry(&go->vidq_active,
				struct go7007_buffer, list);
	go->active_buf = vb;
	spin_unlock(&go->spinlock);
	vb2_buffer_done(&vb_tmp->vb.vb2_buf, VB2_BUF_STATE_DONE);
	return vb;
}
