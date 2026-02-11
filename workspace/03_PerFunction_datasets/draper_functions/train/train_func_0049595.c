play_video_cb(u8 *buf, int count, void *priv)
{
	struct av7110 *av7110 = (struct av7110 *) priv;
	dprintk(2, "av7110:%p, \n", av7110);

	if ((buf[3] & 0xe0) == 0xe0) {
		get_video_format(av7110, buf, count);
		aux_ring_buffer_write(&av7110->avout, buf, count);
	} else
		aux_ring_buffer_write(&av7110->aout, buf, count);
}
