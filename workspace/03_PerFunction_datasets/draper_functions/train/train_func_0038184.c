lookup_symbol(struct keypress sym, char *buf, size_t max)
{
	int i;
	monster_base *race;


	for (i = 1; i < z_info->k_max; i++) {
		if (k_info[i].d_char == (char)sym.code) {
			strnfmt(buf, max, "%c - %s.", (char)sym.code, tval_find_name(k_info[i].tval));
			return;
		}
	}


	for (i = 1; i < z_info->f_max; i++) {
		if (f_info[i].d_char == (char)sym.code) {
			strnfmt(buf, max, "%c - %s.", (char)sym.code, f_info[i].name);
			return;
		}
	}


	for (race = rb_info; race; race = race->next){
		if ((char)sym.code == race->d_char) {
			strnfmt(buf, max, "%c - %s.", (char)sym.code, race->text);
			return;
		}
	}


	strnfmt(buf, max, "%c - %s.", (char)sym.code, "Unknown Symbol");

	return;
}
