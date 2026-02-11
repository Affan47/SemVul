nw_byaddr(struct irs_nw *this, void *net, int len, int af) {
	struct pvt *pvt = (struct pvt *)this->private;

	if (init(this) == -1)
		return (NULL);

	switch (af) {
	case AF_INET:
		return (get1101byaddr(this, net, len));
	default:
		(void)NULL;
	}
	RES_SET_H_ERRNO(pvt->res, NETDB_INTERNAL);
	errno = EAFNOSUPPORT;
	return (NULL);
}
