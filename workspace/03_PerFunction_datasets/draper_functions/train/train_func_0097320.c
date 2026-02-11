print_mac_table(void)
{
	struct hash_iterator hi;
	char buf[BUFSIZE];
	unsigned int key;
	struct mac_info *mi;
	int i = 0;

	printf("--- mac table ---\n");
	hash_iter_set(&hi, &mac_table);
	while ((mi = hash_iter_get(&hi, &key))) {
		sprintf_eth_mac(buf, mi->mac);
		printf("%-24s %s\n", host_lookup(key, hl_mode), buf);
		if (++i % lines_o == 0)
			lines_o_press_key();
	}
	hash_iter_end(&hi);
}
