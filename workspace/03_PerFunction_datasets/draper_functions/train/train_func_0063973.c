cpsw_ale_del_mcast(struct cpsw_ale *ale, u8 *addr, int port_mask,
		       int flags, u16 vid)
{
	u32 ale_entry[ALE_ENTRY_WORDS] = {0, 0, 0};
	int idx;

	idx = cpsw_ale_match_addr(ale, addr, (flags & ALE_VLAN) ? vid : 0);
	if (idx < 0)
		return -EINVAL;

	cpsw_ale_read(ale, idx, ale_entry);

	if (port_mask)
		cpsw_ale_set_port_mask(ale_entry, port_mask);
	else
		cpsw_ale_set_entry_type(ale_entry, ALE_TYPE_FREE);

	cpsw_ale_write(ale, idx, ale_entry);
	return 0;
}
