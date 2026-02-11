my_foreman(int *space, const char *host, int port, time_t stoptime)
{
	int i = 0;
	char full_address[1024];
	if(!domain_name_cache_lookup(host, full_address))
	{
		debug(D_WQ,"Could not resolve %s into an ip address\n",host);
		return 0;
	}
	sprintf(full_address, "%s:%d", full_address, port);

	while(global_catalog[i] != NULL){
		const char *temp_my_master = nvpair_lookup_string(global_catalog[i], "my_master");
		if(temp_my_master && !strcmp(temp_my_master, full_address)){
			char modified_proj[50];
			memset(modified_proj,0,sizeof(modified_proj));
			space_relations(*space, modified_proj);
			sprintf(modified_proj,"%s%s",modified_proj,nvpair_lookup_string(global_catalog[i], "project"));
			nvpair_remove(global_catalog[i], nvpair_lookup_string(global_catalog[i], "project"));
			nvpair_insert_string(global_catalog[i], "project", modified_proj);
			if(resource_mode){
				nvpair_print_table(global_catalog[i], stdout, master_resource_headers);
			}else if(format_mode == FORMAT_TABLE){
				nvpair_print_table(global_catalog[i], stdout, queue_headers);
			}
			int new_space = *space + 1;
			my_foreman(&new_space,nvpair_lookup_string(global_catalog[i], "name"),atoi(nvpair_lookup_string(global_catalog[i], "port")),stoptime);
		}
		i++;
	}

	return 1;
}
