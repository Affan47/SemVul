check_conf(struct menu *menu)
{
	struct symbol *sym;
	struct menu *child;

	if (!menu_is_visible(menu))
		return;

	sym = menu->sym;
	if (sym && !sym_has_value(sym)) {
		if (sym_is_changable(sym) ||
		    (sym_is_choice(sym) && sym_get_tristate_value(sym) == yes)) {
			if (input_mode == listnewconfig) {
				if (sym->name && !sym_is_choice_value(sym)) {
					printf("%s%s\n", CONFIG_, sym->name);
				}
			} else if (input_mode != oldnoconfig) {
				if (!conf_cnt++)
					printf(_("*\n* Restart config...\n*\n"));
				rootEntry = menu_get_parent_menu(menu);
				conf(rootEntry);
			}
		}
	}

	for (child = menu->list; child; child = child->next)
		check_conf(child);
}
