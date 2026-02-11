dump_struct_members(struct list_data *ld, int idx, ulong next)
{
	int i, argc;
	char *p1, *p2;
	char *structname, *members;
	char *arglist[MAXARGS];
	unsigned int radix;

	if (ld->flags & LIST_STRUCT_RADIX_10)
		radix = 10;
	else if (ld->flags & LIST_STRUCT_RADIX_16)
		radix = 16;
	else
		radix = 0;

	structname = GETBUF(strlen(ld->structname[idx])+1);
	members = GETBUF(strlen(ld->structname[idx])+1);

	strcpy(structname, ld->structname[idx]);
	p1 = strstr(structname, ".") + 1;

	p2 = strstr(ld->structname[idx], ".") + 1;
	strcpy(members, p2);
	replace_string(members, ",", ' ');
	argc = parse_line(members, arglist);

	for (i = 0; i < argc; i++) {
		*p1 = NULLCHAR;
		strcat(structname, arglist[i]);
 		dump_struct_member(structname, next - ld->list_head_offset, radix);
	}

	FREEBUF(structname);
	FREEBUF(members);
}
