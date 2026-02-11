data_reset(void){
	struct data_pack *del;
	struct data_pack *delnext;
	struct data_pack *base;
	int step;


	step = 0;
	while(step < HASH_SIZE){
		base = &data_mac_tab[step];
		delnext = base->next_mac;
		while(delnext != base){
			del = delnext;
			delnext = delnext->next_mac;
			free(del);
		}
		step++;
	}


	step = 0;
	while(step < HASH_SIZE){
		base = &data_mac_tab[step];
		base->next_mac = base;
		base->prev_mac = base;
		base = &data_ip_tab[step];
		base->next_ip = base;
		base->prev_ip = base;
		step++;
	}
}
