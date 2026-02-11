aoe_failbuf(struct aoedev *d, struct buf *buf)
{
	if (buf == NULL)
		return;
	buf->iter.bi_size = 0;
	buf->bio->bi_error = -EIO;
	if (buf->nframesout == 0)
		aoe_end_buf(d, buf);
}
