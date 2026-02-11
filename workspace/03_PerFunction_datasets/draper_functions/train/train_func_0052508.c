free_hostent(struct hostent *dst)
{
	int r;
	if (dst->h_name) pkg_free(dst->h_name);
	if (dst->h_aliases){
		for(r=0; dst->h_aliases[r]; r++) {
			pkg_free(dst->h_aliases[r]);
		}
		pkg_free(dst->h_aliases);
	}
	if (dst->h_addr_list){
		for (r=0; dst->h_addr_list[r];r++) {
			pkg_free(dst->h_addr_list[r]);
		}
		pkg_free(dst->h_addr_list);
	}
}
