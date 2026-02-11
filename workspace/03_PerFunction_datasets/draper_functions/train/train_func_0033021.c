cnic_arp_send(nic_t *nic, nic_interface_t *nic_iface, int fd,
			 __u8 *mac_addr, __u32 ip_addr, char *addr_str)
{
	struct ether_header *eth;
	struct ether_arp *arp;
	__u32 dst_ip = ip_addr;
	int pkt_size = sizeof(*eth) + sizeof(*arp);
	int rc;
	struct in_addr addr;
	static const uint8_t multicast_mac[] = {
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	rc = pthread_mutex_trylock(&nic->xmit_mutex);
	if (rc != 0) {
		LOG_DEBUG(PFX "%s: could not get xmit_mutex", nic->log_name);
		return -EAGAIN;
	}

	eth = (*nic->ops->get_tx_pkt) (nic);
	if (eth == NULL) {
		LOG_WARN(PFX "%s: couldn't get tx packet", nic->log_name);
		return -EAGAIN;
	}

	nic_fill_ethernet_header(nic_iface, eth,
				 nic->mac_addr, (void *)multicast_mac,
				 &pkt_size, (void *)&arp, ETHERTYPE_ARP);

	arp->arp_hrd = htons(ARPHRD_ETHER);
	arp->arp_pro = htons(ETHERTYPE_IP);
	arp->arp_hln = ETH_ALEN;
	arp->arp_pln = 4;
	arp->arp_op = htons(ARPOP_REQUEST);
	memcpy(arp->arp_sha, nic->mac_addr, ETH_ALEN);
	memset(arp->arp_tha, 0, ETH_ALEN);


	memcpy(arp->arp_spa, nic_iface->ustack.hostaddr, 4);
	memcpy(arp->arp_tpa, &dst_ip, 4);

	(*nic->nic_library->ops->start_xmit) (nic, pkt_size,
					      (nic_iface->vlan_priority << 12) |
					      nic_iface->vlan_id);

	memcpy(&addr.s_addr, &dst_ip, sizeof(addr.s_addr));
	LOG_DEBUG(PFX "%s: Sent cnic arp request for IP: %s",
		  nic->log_name, addr_str);

	return 0;
}
