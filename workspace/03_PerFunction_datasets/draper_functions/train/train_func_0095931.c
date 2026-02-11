xenbus_map_ring(struct xenbus_device *dev, grant_ref_t *gnt_refs,
		    unsigned int nr_grefs, grant_handle_t *handles,
		    unsigned long *vaddrs, bool *leaked)
{
	phys_addr_t phys_addrs[XENBUS_MAX_RING_GRANTS];
	int i;

	if (nr_grefs > XENBUS_MAX_RING_GRANTS)
		return -EINVAL;

	for (i = 0; i < nr_grefs; i++)
		phys_addrs[i] = (unsigned long)vaddrs[i];

	return __xenbus_map_ring(dev, gnt_refs, nr_grefs, handles,
				 phys_addrs, GNTMAP_host_map, leaked);
}
