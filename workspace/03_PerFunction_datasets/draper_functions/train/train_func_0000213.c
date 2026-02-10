cli_print_ip_range_list(struct cli_session* cs, ip_range_list_t *value, const char* name, int changeable)
{
	if(cs && cs->ts && name && value && value->ranges_number && value->rs) {
		const char *sc="";
		if(changeable==1)
			sc=" (*)";
		else if(changeable==2)
			sc=" (**)";
		size_t i;
		for(i=0;i<value->ranges_number;++i) {
			if(value->rs[i].realm[0]) {
				if(cs->realm[0] && strcmp(cs->realm,value->rs[i].realm)) {
					continue;
				} else {
					myprintf(cs,"  %s: %s (%s)%s\n",name,value->rs[i].str,value->rs[i].realm,sc);
				}
			} else {
				myprintf(cs,"  %s: %s%s\n",name,value->rs[i].str,sc);
			}
		}
	}
}
