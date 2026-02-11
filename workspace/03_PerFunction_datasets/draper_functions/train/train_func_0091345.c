dump_struct_members_for_tree(struct tree_data *td, int idx, ulong struct_p)
{
	int i, argc;
	uint print_radix;
	char *p1;
	char *structname, *members;
	char *arglist[MAXARGS];

	if (td->flags & TREE_STRUCT_RADIX_10)
		print_radix = 10;
	else if (td->flags & TREE_STRUCT_RADIX_16)
		print_radix = 16;
	else
		print_radix = 0;

	structname = GETBUF(strlen(td->structname[idx])+1);
	members = GETBUF(strlen(td->structname[idx])+1);

	strcpy(structname, td->structname[idx]);
	p1 = strstr(structname, ".") + 1;

	strcpy(members, p1);
	replace_string(members, ",", ' ');
	argc = parse_line(members, arglist);

	for (i = 0; i <argc; i++) {
		*p1 = NULLCHAR;
		strcat(structname, arglist[i]);
		dump_struct_member(structname, struct_p, print_radix);
	}

	FREEBUF(structname);
	FREEBUF(members);
}
