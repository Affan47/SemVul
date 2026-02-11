update_hash_table_mac_address(struct pxa168_eth_private *pep,
					  unsigned char *oaddr,
					  unsigned char *addr)
{

	if (oaddr)
		add_del_hash_entry(pep, oaddr, 1, 0, HASH_DELETE);

	add_del_hash_entry(pep, addr, 1, 0, HASH_ADD);
}
