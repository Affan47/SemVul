pcmcia_do_get_tuple(struct pcmcia_device *p_dev, tuple_t *tuple,
			       void *priv)
{
	struct pcmcia_loop_get *get = priv;

	*get->buf = kzalloc(tuple->TupleDataLen, GFP_KERNEL);
	if (*get->buf) {
		get->len = tuple->TupleDataLen;
		memcpy(*get->buf, tuple->TupleData, tuple->TupleDataLen);
	} else
		dev_dbg(&p_dev->dev, "do_get_tuple: out of memory\n");
	return 0;
}
