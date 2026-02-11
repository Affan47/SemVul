link_nvpair_read( struct link *l, time_t stoptime )
{
	struct nvpair *nv = nvpair_create();
	char line[65536];
	int lines = 0;

	while(link_readline(l, line, sizeof(line), stoptime)) {
		string_chomp(line);
		if(!line[0])
			break;
		nvpair_parse(nv, line);
		lines++;
	}

	if(lines) {
		return nv;
	} else {
		nvpair_delete(nv);
		return 0;
	}
}
