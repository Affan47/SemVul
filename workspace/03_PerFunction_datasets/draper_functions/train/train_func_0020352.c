__tlb_clear_slave(struct bonding *bond, struct slave *slave,
			 int save_load)
{
	struct tlb_client_info *tx_hash_table;
	u32 index;


	tx_hash_table = BOND_ALB_INFO(bond).tx_hashtbl;


	if (tx_hash_table) {
		index = SLAVE_TLB_INFO(slave).head;
		while (index != TLB_NULL_INDEX) {
			u32 next_index = tx_hash_table[index].next;
			tlb_init_table_entry(&tx_hash_table[index], save_load);
			index = next_index;
		}
	}

	tlb_init_slave(slave);
}
