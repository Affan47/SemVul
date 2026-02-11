nfs_dns_resolve_name(struct net *net, char *name,
		size_t namelen, struct sockaddr *sa, size_t salen)
{
	struct nfs_dns_ent key = {
		.hostname = name,
		.namelen = namelen,
	};
	struct nfs_dns_ent *item = NULL;
	ssize_t ret;
	struct nfs_net *nn = net_generic(net, nfs_net_id);

	ret = do_cache_lookup_wait(nn->nfs_dns_resolve, &key, &item);
	if (ret == 0) {
		if (salen >= item->addrlen) {
			memcpy(sa, &item->addr, item->addrlen);
			ret = item->addrlen;
		} else
			ret = -EOVERFLOW;
		cache_put(&item->h, nn->nfs_dns_resolve);
	} else if (ret == -ENOENT)
		ret = -ESRCH;
	return ret;
}
