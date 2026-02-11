find_lease_by_hw_addr (struct lease **lp,
			   const unsigned char *hwaddr, unsigned hwlen,
			   const char *file, int line)
{
	if (hwlen == 0)
		return (0);


	if ((hwlen == 1) && (hwaddr[0] == HTYPE_INFINIBAND))
		return (0);

	return (lease_id_hash_lookup(lp, lease_hw_addr_hash, hwaddr, hwlen,
				     file, line));
}
