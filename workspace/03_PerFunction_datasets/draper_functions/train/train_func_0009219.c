addr_hash(const ioa_addr *addr)
{
	if(!addr)
		return 0;

	u32bits ret = 0;
	if (addr->ss.sa_family == AF_INET) {
		ret = hash_int32(addr->s4.sin_addr.s_addr + addr->s4.sin_port);
	} else {
		const u64bits *a = (const u64bits *) (&(addr->s6.sin6_addr));
		ret = (u32bits)((hash_int64(a[0])<<3) + (hash_int64(a[1] + addr->s6.sin6_port)));
	}
	return ret;
}
