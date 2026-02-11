unset_all_on_page(winid  window, tty_menu_item *page_start, tty_menu_item *page_end)
{
    tty_menu_item *curr;
    int n;

    for (n = 0, curr = page_start; curr != page_end; n++, curr = curr->next)
	if (curr->identifier.a_void && curr->selected) {
	    curr->selected = false;
	    curr->count = -1L;
	    set_item_state(window, n, curr);
	}
}
