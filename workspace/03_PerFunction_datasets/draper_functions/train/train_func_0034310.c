parse_atom(const char *atom, const char *ep)
{
	const char *sp;
	int i, at;

	sp = atom;
	if (*sp == '*' && sp < ep)
		sp++;
	if (ep <= sp)
		die("malformed field name: %.*s", (int)(ep-atom), atom);


	for (i = 0; i < used_atom_cnt; i++) {
		int len = strlen(used_atom[i]);
		if (len == ep - atom && !memcmp(used_atom[i], atom, len))
			return i;
	}


	for (i = 0; i < ARRAY_SIZE(valid_atom); i++) {
		int len = strlen(valid_atom[i].name);


		const char *formatp = strchr(sp, ':');
		if (!formatp || ep < formatp)
			formatp = ep;
		if (len == formatp - sp && !memcmp(valid_atom[i].name, sp, len))
			break;
	}

	if (ARRAY_SIZE(valid_atom) <= i)
		die("unknown field name: %.*s", (int)(ep-atom), atom);


	at = used_atom_cnt;
	used_atom_cnt++;
	used_atom = xrealloc(used_atom,
			     (sizeof *used_atom) * used_atom_cnt);
	used_atom_type = xrealloc(used_atom_type,
				  (sizeof(*used_atom_type) * used_atom_cnt));
	used_atom[at] = xmemdupz(atom, ep - atom);
	used_atom_type[at] = valid_atom[i].cmp_type;
	if (*atom == '*')
		need_tagged = 1;
	if (!strcmp(used_atom[at], "symref"))
		need_symref = 1;
	return at;
}
