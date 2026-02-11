add_contact_and_accounts(struct contact *c)
{
	LList *l;
	for (l = c->accounts; l; l = l->next) {
		eb_account *ea = l->data;
		if (status_show == 0 || status_show == 1 || ea->online) {
			add_account_line(ea);
			buddy_update_icon(ea);
		}
	}
}
