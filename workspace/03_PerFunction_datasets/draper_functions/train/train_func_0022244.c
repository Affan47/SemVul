dump_header(struct fpga_config* cfg)
{
	int i;
	for (i = 0; i < sizeof(cfg->header_str)
			/sizeof(cfg->header_str[0]); i++) {
		printf("header_str_%c %s\n", 'a'+i,
			cfg->header_str[i]);
	}
}
