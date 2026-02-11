__tlb_choose_channel(struct bonding *bond, u32 hash_index,
						u32 skb_len)
{
	struct alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	struct tlb_client_info *hash_table;
	struct slave *assigned_slave;

	hash_table = bond_info->tx_hashtbl;
	assigned_slave = hash_table[hash_index].tx_slave;
	if (!assigned_slave) {
		assigned_slave = tlb_get_least_loaded_slave(bond);

		if (assigned_slave) {
			struct tlb_slave_info *slave_info =
				&(SLAVE_TLB_INFO(assigned_slave));
			u32 next_index = slave_info->head;

			hash_table[hash_index].tx_slave = assigned_slave;
			hash_table[hash_index].next = next_index;
			hash_table[hash_index].prev = TLB_NULL_INDEX;

			if (next_index != TLB_NULL_INDEX)
				hash_table[next_index].prev = hash_index;

			slave_info->head = hash_index;
			slave_info->load +=
				hash_table[hash_index].load_history;
		}
	}

	if (assigned_slave)
		hash_table[hash_index].tx_bytes += skb_len;

	return assigned_slave;
}
