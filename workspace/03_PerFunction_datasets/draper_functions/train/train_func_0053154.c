locate_file_arch(visearch *p, char *name) {
	int i, sl;

	sl = strlen(name);

	if (sl == 0)
		return 1;


	for (i = 0x10000; i < (p->asize - sl); i++) {
		if (p->abuf[i] == name[0]) {
			if (strncmp((char *)&p->abuf[i], name, sl) == 0) {
				int sto;

				if (p->verb)
					printf("Located driver entry '%s' at offset 0x%x\n",name,i);
				i += sl;
				if (i >= (p->asize - 1))
					return 1;
				sto = p->abuf[i];
				i += (4 + sto) * 4;
				if (i >= (p->asize - 4))
					return 1;
				p->off =  p->abuf[i + 0];
				p->off += (p->abuf[i + 1] << 8);
				p->off += (p->abuf[i + 2] << 16);
				p->off += (p->abuf[i + 3] << 24);
				p->off += p->vbase;
				if (p->off >= p->asize - 10)
					return 1;
				if (p->verb)
					printf("Located driver file '%s' at offset 0x%x\n",name,p->off);
				return 0;
			}
		}
	}
	return 1;
}
