check_conf(struct menu *menu)
{
	struct symbol *sym;
	struct menu *child;

	if (!menu_is_visible(menu))
		return;

	sym = menu->sym;
	if (sym) {
		if (sym_is_changable(sym) && !sym_has_value(sym)) {
			if (!conf_cnt++)
				printf("*\n* Restart config...\n*\n");
			rootEntry = menu_get_parent_menu(menu);
			conf(rootEntry);
		}
		if (sym_is_choice(sym) && sym_get_tristate_value(sym) != mod)
			return;
	}

	for (child = menu->list; child; child = child->next)
		check_conf(child);
}
