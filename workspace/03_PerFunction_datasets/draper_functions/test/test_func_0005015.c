print_ldif_add(FILE *s, char *dn, LDAPMod **mods)
{
	fputc('\n', s);
	print_ldif_line(s, "dn", dn, -1);
	fputs("changetype: add\n", s);

	for (; *mods; mods++) {
		LDAPMod *mod = *mods;
		print_ldif_bervals(s, mod->mod_type, mod->mod_bvalues);
	}
	if (ferror(s)) syserr();
}
