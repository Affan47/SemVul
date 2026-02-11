um_remove_card(DESCRIPTOR *d)
{
	diva_os_spin_lock_magic_t old_irql;
	udiva_card *card = NULL;

	if (!(card = find_card_in_list(d))) {
		DBG_ERR(("cannot find card to remove"));
		return;
	}
	diva_user_mode_idi_remove_adapter(card->Id);
	diva_os_enter_spin_lock(&ll_lock, &old_irql, "remove card");
	list_del(&card->list);
	diva_os_leave_spin_lock(&ll_lock, &old_irql, "remove card");
	DBG_LOG(("idi proc entry removed for card %d", card->Id));
	diva_os_free(0, card);
}
