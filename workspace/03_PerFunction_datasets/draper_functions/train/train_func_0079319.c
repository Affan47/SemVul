cup_init(void)
{
	int i;
	struct widget *mo = cup_menu_skier->kids;
	char *title;

	for (i = 0; i < cup_sk_limit; i++)
		cup_sk_array[i] = NULL;

	for (mo = cup_menu_skier->kids, i = 0; mo; SWITCH(mo)) {
		if ((mo = menu_ticked(mo)) == NULL)
			break;
		cup_menu_skier->current = mo;

		cup_sk_array[i++] = sk_rewind(menu_selected_number(cup_menu_skier));
	}

	cup_sk_counter = i-1;

	if (cup_hl_array == NULL)
		cup_hl_array = xmalloc(sizeof(struct s_hill *) * hl_counter);

	for (i = 0; i < hl_counter; i++)
		cup_hl_array[i++] = NULL;

	for (mo = cup_menu_hill->kids, i = 0; mo; SWITCH(mo)) {
		if ((mo = menu_ticked(mo)) == NULL)
			break;
		cup_menu_hill->current = mo;

		title = menu_selected_caption(cup_menu_hill);
		cup_hl_array[i++] = hl_find(title, NULL);
	}

	cup_hl_counter = i-1;

	if (cup_sk_array[0] && cup_hl_array[0]) {
		cup_sk_no = 0;
		cup_hl_no = 0;

		for (i = 0; i < cup_sk_counter; i++) {
			cup_sk_array[i]->points = 0;
			cup_sk_array[i]->hill = cup_hl_array[0];

		}

		rs_actions(cup_show, mn_scr_show);

		sk_array = cup_sk_array;
		sk_head = cup_sk_head;
		sk_tail = cup_sk_tail;

		state = A_cup;
	}
}
