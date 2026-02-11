ctl2_find_name(
	msft_typelib_t *typelib,
	char *name)
{
    int offset;
    int *namestruct;

    offset = typelib->typelib_namehash_segment[name[2] & 0x7f];
    while (offset != -1) {
	namestruct = (int *)&typelib->typelib_segment_data[MSFT_SEG_NAME][offset];

	if (!((namestruct[2] ^ *((int *)name)) & 0xffff00ff)) {

	    if (!strncasecmp(name+4, (void *)(namestruct+3), name[0])) break;
	}


	offset = namestruct[1];
    }

    return offset;
}
