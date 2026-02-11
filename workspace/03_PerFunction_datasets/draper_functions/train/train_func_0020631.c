reloc_apply(Object *reloc, byte *data)
{
	ht_ne_reloc_entry *e = (ht_ne_reloc_entry*)reloc;

	switch (e->mode & NE_RT_MASK) {
		case NE_RT_OFS8:
			createForeignInt(data, e->ofs, 1, little_endian);
			break;
		case NE_RT_SEG16:
			createForeignInt(data, e->seg, 2, little_endian);
			break;
		case NE_RT_OFS16:
			createForeignInt(data, e->ofs, 2, little_endian);
			break;
		case NE_RT_PTR32:
			createForeignInt(data, e->ofs, 2, little_endian);
			createForeignInt(data+2, e->seg, 2, little_endian);
			break;
		case NE_RT_OFS32:
			createForeignInt(data, e->ofs, 4, little_endian);
			break;
		case NE_RT_PTR48:
			createForeignInt(data, e->ofs, 4, little_endian);
			createForeignInt(data+4, e->seg, 2, little_endian);
			break;
	}
}
