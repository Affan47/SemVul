vbi_buffer_setup(struct videobuf_queue *q,
			    unsigned int *count, unsigned int *size)
{
	struct bttv_fh *fh = q->priv_data;
	struct bttv *btv = fh->btv;

	if (0 == *count)
		*count = vbibufs;

	*size = IMAGE_SIZE(&fh->vbi_fmt.fmt);

	dprintk("setup: samples=%u start=%d,%d count=%u,%u\n",
		fh->vbi_fmt.fmt.samples_per_line,
		fh->vbi_fmt.fmt.start[0],
		fh->vbi_fmt.fmt.start[1],
		fh->vbi_fmt.fmt.count[0],
		fh->vbi_fmt.fmt.count[1]);

	return 0;
}
