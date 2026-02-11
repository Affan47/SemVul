rrset_list_add(rrset_list_t **head, knot_rrset_t *rrsig)
{
	if (*head == NULL) {
		*head = xmalloc(sizeof(rrset_list_t));
		(*head)->next = NULL;
		(*head)->data = rrsig;
	} else {
		rrset_list_t *tmp = xmalloc(sizeof(*tmp));
		tmp->next = *head;
		tmp->data = rrsig;
		*head = tmp;
	}

	dbg_zload_verb("zp: rrset_add: Added RRSIG %p to list.\n", rrsig);

	return KNOT_EOK;
}
