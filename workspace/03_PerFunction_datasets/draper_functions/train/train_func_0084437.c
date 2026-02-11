read_relocs(FILE *fp)
{
	int i,j;
	for (i = 0; i < ehdr.e_shnum; i++) {
		struct section *sec = &secs[i];
		if (sec->shdr.sh_type != SHT_REL) {
			continue;
		}
		sec->reltab = malloc(sec->shdr.sh_size);
		if (!sec->reltab) {
			die("malloc of %d bytes for relocs failed\n",
				sec->shdr.sh_size);
		}
		if (fseek(fp, sec->shdr.sh_offset, SEEK_SET) < 0) {
			die("Seek to %d failed: %s\n",
				sec->shdr.sh_offset, strerror(errno));
		}
		if (fread(sec->reltab, 1, sec->shdr.sh_size, fp)
		    != sec->shdr.sh_size) {
			die("Cannot read symbol table: %s\n",
				strerror(errno));
		}
		for (j = 0; j < sec->shdr.sh_size/sizeof(Elf32_Rel); j++) {
			Elf32_Rel *rel = &sec->reltab[j];
			rel->r_offset = elf32_to_cpu(rel->r_offset);
			rel->r_info   = elf32_to_cpu(rel->r_info);
		}
	}
}
