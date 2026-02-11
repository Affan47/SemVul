data_exist(struct ether_addr *mac,
                             struct capt *idcap){
	struct data_pack *base;
	struct data_pack *find;
	int hash;


	hash = DATA_MAC_HASH(mac);
	base = &data_mac_tab[hash];
	find = base->next_mac;
	while(find != base){
		if(find->cap_id == idcap &&
		   DATA_CMP(&find->mac, mac) == 0){
			return find;
		}
		find = find->next_mac;
	}
	return(NULL);
}
