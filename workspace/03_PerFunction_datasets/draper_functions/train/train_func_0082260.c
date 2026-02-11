__videobuf_copy_stream(struct videobuf_queue *q,
				  struct videobuf_buffer *buf,
				  char __user *data, size_t count, size_t pos,
				  int vbihack, int nonblocking)
{
	unsigned int *fc = CALLPTR(q, vaddr, buf);

	if (vbihack) {


		fc += (buf->size >> 2) - 1;
		*fc = buf->field_count >> 1;
		dprintk(1, "vbihack: %d\n", *fc);
	}


	count = __videobuf_copy_to_user(q, buf, data, count, nonblocking);

	if ((count == -EFAULT) && (pos == 0))
		return -EFAULT;

	return count;
}
