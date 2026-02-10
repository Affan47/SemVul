read_cis_cache(struct pcmcia_socket *s, int attr, u_int addr,
			size_t len, void *ptr)
{
	struct cis_cache_entry *cis;
	int ret = 0;

	if (s->state & SOCKET_CARDBUS)
		return -EINVAL;

	mutex_lock(&s->ops_mutex);
	if (s->fake_cis) {
		if (s->fake_cis_len >= addr+len)
			memcpy(ptr, s->fake_cis+addr, len);
		else {
			memset(ptr, 0xff, len);
			ret = -EINVAL;
		}
		mutex_unlock(&s->ops_mutex);
		return ret;
	}

	list_for_each_entry(cis, &s->cis_cache, node) {
		if (cis->addr == addr && cis->len == len && cis->attr == attr) {
			memcpy(ptr, cis->cache, len);
			mutex_unlock(&s->ops_mutex);
			return 0;
		}
	}

	ret = pcmcia_read_cis_mem(s, attr, addr, len, ptr);

	if (ret == 0) {

		cis = kmalloc(sizeof(struct cis_cache_entry) + len, GFP_KERNEL);
		if (cis) {
			cis->addr = addr;
			cis->len = len;
			cis->attr = attr;
			memcpy(cis->cache, ptr, len);
			list_add(&cis->node, &s->cis_cache);
		}
	}
	mutex_unlock(&s->ops_mutex);

	return ret;
}
