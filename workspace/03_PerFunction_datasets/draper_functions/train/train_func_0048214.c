is_ip6_in_address_list(struct prefix_list *plist, struct in6_addr *target){
	unsigned int i, j;

	for(i=0; i < plist->nprefix; i++){
		for(j=0; j < 8; j++){
			if(target->s6_addr16[j] != (plist->prefix[i])->ip6.s6_addr16[j])
				break;
		}

		if(j == 8)
			return 1;
	}

	return 0;
}
