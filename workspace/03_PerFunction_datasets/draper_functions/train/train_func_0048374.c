find_account_for_protocol(struct contact *c, int service)
{
	LList *l = c->accounts;
	while (l && l->data) {
		eb_account *a = (eb_account *)l->data;
		if (a && a->service_id == service)
			return a;
		l = l->next;
	}
	return NULL;
}
