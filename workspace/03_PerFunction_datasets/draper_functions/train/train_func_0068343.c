videobuf_status(struct videobuf_queue *q, struct v4l2_buffer *b,
			    struct videobuf_buffer *vb, enum v4l2_buf_type type)
{
	MAGIC_CHECK(vb->magic, MAGIC_BUFFER);
	MAGIC_CHECK(q->int_ops->magic, MAGIC_QTYPE_OPS);

	b->index    = vb->i;
	b->type     = type;

	b->memory   = vb->memory;
	switch (b->memory) {
	case V4L2_MEMORY_MMAP:
		b->m.offset  = vb->boff;
		b->length    = vb->bsize;
		break;
	case V4L2_MEMORY_USERPTR:
		b->m.userptr = vb->baddr;
		b->length    = vb->bsize;
		break;
	case V4L2_MEMORY_OVERLAY:
		b->m.offset  = vb->boff;
		break;
	case V4L2_MEMORY_DMABUF:

		break;
	}

	b->flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	if (vb->map)
		b->flags |= V4L2_BUF_FLAG_MAPPED;

	switch (vb->state) {
	case VIDEOBUF_PREPARED:
	case VIDEOBUF_QUEUED:
	case VIDEOBUF_ACTIVE:
		b->flags |= V4L2_BUF_FLAG_QUEUED;
		break;
	case VIDEOBUF_ERROR:
		b->flags |= V4L2_BUF_FLAG_ERROR;

	case VIDEOBUF_DONE:
		b->flags |= V4L2_BUF_FLAG_DONE;
		break;
	case VIDEOBUF_NEEDS_INIT:
	case VIDEOBUF_IDLE:

		break;
	}

	b->field     = vb->field;
	b->timestamp = vb->ts;
	b->bytesused = vb->size;
	b->sequence  = vb->field_count >> 1;
}
