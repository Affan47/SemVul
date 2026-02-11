server_lookup(const char *host, time_t stoptime)
{
	if(server_table_load(stoptime)) {
		return hash_table_lookup(server_table, host);
	} else {
		return 0;
	}
}
