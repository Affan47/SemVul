find_free_or_expired_nip(const uint8_t *safe_mac)
{
	uint32_t addr;
	struct dyn_lease *oldest_lease = NULL;

	addr = server_config.start_ip;
	for (; addr <= server_config.end_ip; addr++) {
		uint32_t nip;
		struct dyn_lease *lease;


		if ((addr & 0xff) == 0)
			continue;

		if ((addr & 0xff) == 0xff)
			continue;
		nip = htonl(addr);

		if (is_nip_reserved(server_config.static_leases, nip))
			continue;

		lease = find_lease_by_nip(nip);
		if (!lease) {

			if (nobody_responds_to_arp(nip, safe_mac))
				return nip;
		} else {
			if (!oldest_lease || lease->expires < oldest_lease->expires)
				oldest_lease = lease;
		}
	}

	if (oldest_lease
	 && is_expired_lease(oldest_lease)
	 && nobody_responds_to_arp(oldest_lease->lease_nip, safe_mac)
	) {
		return oldest_lease->lease_nip;
	}

	return 0;
}
