verify_cis_cache(struct pcmcia_socket *s)
{
	struct cis_cache_entry *cis;
	char *buf;
	int ret;

	if (s->state & SOCKET_CARDBUS)
		return -EINVAL;

	buf = kmalloc(256, GFP_KERNEL);
	if (buf == NULL) {
		dev_warn(&s->dev, "no memory for verifying CIS\n");
		return -ENOMEM;
	}
	mutex_lock(&s->ops_mutex);
	list_for_each_entry(cis, &s->cis_cache, node) {
		int len = cis->len;

		if (len > 256)
			len = 256;

		ret = pcmcia_read_cis_mem(s, cis->attr, cis->addr, len, buf);
		if (ret || memcmp(buf, cis->cache, len) != 0) {
			kfree(buf);
			mutex_unlock(&s->ops_mutex);
			return -1;
		}
	}
	kfree(buf);
	mutex_unlock(&s->ops_mutex);
	return 0;
}
