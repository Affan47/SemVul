sens_timeout_add(struct ether_addr *mac, struct in_addr ipb,
                      struct capt *idcap){
	struct tmouts *new_tmout;
	struct tmouts *base;
	int hash;


	if(free_start->next_chain == free_start){
		logmsg(LOG_WARNING,
		       "[%s %d] Timeouts table full: more than %d timeouts used",
		       __FILE__, __LINE__, MAX_DATA);
		return;
	}


	new_tmout = free_start->next_chain;
	DATA_CPY(&new_tmout->mac, mac);
	new_tmout->idcap = idcap;
	new_tmout->ip_d.s_addr = ipb.s_addr;
	new_tmout->last.tv_sec = current_t.tv_sec +
	                         config[CF_ANTIFLOOD_INTER].valeur.integer;
	new_tmout->last.tv_usec = current_t.tv_usec;


	new_tmout->prev_chain->next_chain = new_tmout->next_chain;
	new_tmout->next_chain->prev_chain = new_tmout->prev_chain;


	hash = SENS_TIMEOUT_HASH(mac, ipb.s_addr);
	base = &tmout_h[hash];
	base->next_hash->prev_hash = new_tmout;
	new_tmout->next_hash = base->next_hash;
	base->next_hash = new_tmout;
	new_tmout->prev_hash = base;


	used_start->prev_chain->next_chain = new_tmout;
	new_tmout->prev_chain = used_start->prev_chain;
	used_start->prev_chain = new_tmout;
	new_tmout->next_chain = used_start;
}
