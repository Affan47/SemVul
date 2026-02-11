usbtv_image_chunk(struct usbtv *usbtv, __be32 *chunk)
{
	int frame_id, odd, chunk_no;
	u32 *frame;
	struct usbtv_buf *buf;
	unsigned long flags;


	if (!USBTV_MAGIC_OK(chunk))
		return;
	frame_id = USBTV_FRAME_ID(chunk);
	odd = USBTV_ODD(chunk);
	chunk_no = USBTV_CHUNK_NO(chunk);
	if (chunk_no >= usbtv->n_chunks)
		return;


	if (chunk_no == 0) {
		usbtv->frame_id = frame_id;
		usbtv->chunks_done = 0;
	}

	if (usbtv->frame_id != frame_id)
		return;

	spin_lock_irqsave(&usbtv->buflock, flags);
	if (list_empty(&usbtv->bufs)) {

		spin_unlock_irqrestore(&usbtv->buflock, flags);
		return;
	}


	buf = list_first_entry(&usbtv->bufs, struct usbtv_buf, list);
	frame = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);


	usbtv_chunk_to_vbuf(frame, &chunk[1], chunk_no, odd);
	usbtv->chunks_done++;


	if (odd && chunk_no == usbtv->n_chunks-1) {
		int size = vb2_plane_size(&buf->vb.vb2_buf, 0);
		enum vb2_buffer_state state = usbtv->chunks_done ==
						usbtv->n_chunks ?
						VB2_BUF_STATE_DONE :
						VB2_BUF_STATE_ERROR;

		buf->vb.field = V4L2_FIELD_INTERLACED;
		buf->vb.sequence = usbtv->sequence++;
		v4l2_get_timestamp(&buf->vb.timestamp);
		vb2_set_plane_payload(&buf->vb.vb2_buf, 0, size);
		vb2_buffer_done(&buf->vb.vb2_buf, state);
		list_del(&buf->list);
	}

	spin_unlock_irqrestore(&usbtv->buflock, flags);
}
