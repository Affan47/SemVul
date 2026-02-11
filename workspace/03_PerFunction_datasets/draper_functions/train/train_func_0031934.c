invert_all(winid window, tty_menu_item *page_start, tty_menu_item *page_end, char acc)
{
    tty_menu_item *curr;
    bool on_curr_page;
    struct WinDesc *cw =  wins[window];

    invert_all_on_page(window, page_start, page_end, acc);


    for (on_curr_page = false, curr = cw->mlist; curr; curr = curr->next) {
	if (curr == page_start)
	    on_curr_page = true;
	else if (curr == page_end)
	    on_curr_page = false;

	if (!on_curr_page && curr->identifier.a_void
				&& (acc == 0 || curr->gselector == acc)) {
	    if (curr->selected) {
		curr->selected = false;
		curr->count = -1;
	    } else
		curr->selected = true;
	}
    }
}
