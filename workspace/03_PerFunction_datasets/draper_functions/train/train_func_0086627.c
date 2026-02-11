rlb_req_update_subnet_clients(struct bonding *bond, __be32 src_ip)
{
	struct alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	struct rlb_client_info *client_info;
	u32 hash_index;

	spin_lock(&bond->mode_lock);

	hash_index = bond_info->rx_hashtbl_used_head;
	for (; hash_index != RLB_NULL_INDEX;
	     hash_index = client_info->used_next) {
		client_info = &(bond_info->rx_hashtbl[hash_index]);

		if (!client_info->slave) {
			netdev_err(bond->dev, "found a client with no channel in the client's hash table\n");
			continue;
		}


		if ((client_info->ip_src == src_ip) &&
		    !ether_addr_equal_64bits(client_info->slave->dev->dev_addr,
					     bond->dev->dev_addr) &&
		    !ether_addr_equal_64bits(client_info->mac_dst, mac_bcast)) {
			client_info->ntt = 1;
			bond_info->rx_ntt = 1;
		}
	}

	spin_unlock(&bond->mode_lock);
}
