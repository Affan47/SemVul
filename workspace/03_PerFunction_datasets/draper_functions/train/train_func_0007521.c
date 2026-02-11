mgt_oidtonum(u32 oid)
{
	int i;

	for (i = 0; i < OID_NUM_LAST; i++)
		if (isl_oid[i].oid == oid)
			return i;

	printk(KERN_DEBUG "looking for an unknown oid 0x%x", oid);

	return OID_NUM_LAST;
}
