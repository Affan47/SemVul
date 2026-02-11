do_cmd_redraw(void)
{
	int j;

	term *old = Term;


	Term_flush();


	flush();

	if (character_dungeon)
		verify_panel();


	Term_xtra(TERM_XTRA_REACT, 0);


	p_ptr->notice |= (PN_COMBINE | PN_REORDER);


	p_ptr->update |= (PU_TORCH);


	p_ptr->update |= (PU_BONUS | PU_HP | PU_MANA | PU_SPELLS);


	p_ptr->update |= (PU_FORGET_VIEW | PU_UPDATE_VIEW | PU_MONSTERS);


	p_ptr->redraw |= (PR_BASIC | PR_EXTRA | PR_MAP | PR_INVEN | PR_EQUIP |
	                  PR_MESSAGE | PR_MONSTER | PR_OBJECT |
					  PR_MONLIST | PR_ITEMLIST);


	Term_clear();


	handle_stuff(p_ptr);


	if (0 != character_dungeon)
		move_cursor_relative(p_ptr->px, p_ptr->py);


	for (j = 0; j < ANGBAND_TERM_MAX; j++)
	{
		if (!angband_term[j]) continue;

		Term_activate(angband_term[j]);
		Term_redraw();
		Term_fresh();
		Term_activate(old);
	}
}
