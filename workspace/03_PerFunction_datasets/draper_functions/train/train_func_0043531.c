dhcpv4_get_ip(struct dhcpv4_serv *serv, uint32_t *yiaddr, uint32_t *siaddr, int *mask)
{
	int i, k;

	if (!serv->range)
		return 0;

	pthread_mutex_lock(&serv->range->lock);

	while (1) {
		for (i = serv->range->pos; i < serv->range->len; i++) {
			k = ffsl(serv->range->free[i]);
			if (k) {
				serv->range->free[i] &= ~(1 << (k - 1));
				serv->range->pos = i;
				pthread_mutex_unlock(&serv->range->lock);
				*yiaddr = htonl(serv->range->startip + i * 8 * sizeof(long) + k - 1);
				*siaddr = htonl(serv->range->routerip);
				*mask = serv->range->mask;
				return 1;
			}
		}

		if (serv->range->pos == 0)
			break;

		serv->range->pos = 0;
	}

	pthread_mutex_unlock(&serv->range->lock);
	return 0;
}
