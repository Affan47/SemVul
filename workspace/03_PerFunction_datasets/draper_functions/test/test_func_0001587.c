do_cmd_inven(void)
{
	ui_event e;
	int diff = weight_remaining();


	p_ptr->command_wrk = (USE_INVEN);


	screen_save();


	item_tester_full = TRUE;


	show_inven(OLIST_WEIGHT | OLIST_QUIVER);


	item_tester_full = FALSE;


	prt(format("(Inventory) Burden %d.%d lb (%d.%d lb %s). Command: ",
		        p_ptr->total_weight / 10, p_ptr->total_weight % 10,
		        abs(diff) / 10, abs(diff) % 10,
		        (diff < 0 ? "overweight" : "remaining")),
	    0, 0);


	e = inkey_ex();
	if (!(e.type == EVT_KBRD && e.key.code == ESCAPE))
		Term_event_push(&e);


	screen_load();
}
