parser_free_conf(config_parsed_t *cfg)
{
	section_list_t *sec;
	if (cfg)
	{
		parser_free_kwlist(cfg->config_setup);
		while (cfg->conn_first)
		{
			sec = cfg->conn_first;
			cfg->conn_first = cfg->conn_first->next;
			free(sec->name);
			parser_free_kwlist(sec->kw);
			free(sec);
		}
		while (cfg->ca_first)
		{
			sec = cfg->ca_first;
			cfg->ca_first = cfg->ca_first->next;
			free(sec->name);
			parser_free_kwlist(sec->kw);
			free(sec);
		}
		free(cfg);
	}
}
