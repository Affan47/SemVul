al_insert(LIST *ald, void *unew)
{
	struct al_head	*curr;
	struct al_head	*prev;
	struct al_head	*new_head;
	char		*new_char;


	new_head = (struct al_head *) malloc((unsigned)
			(ald->al_elemsize + sizeof(struct al_head)));

	if (new_head == 0) {
		return((void *) 0);
	}

	new_char = al_body(new_head);
	memcpy(new_char, (char *) unew, ald->al_elemsize);
	curr = ald->al_ltop;
	prev = 0;

	while ((curr != 0) &&
		(((*(ald->al_comp))(new_char, al_body(curr))) >= 0)) {

		prev = curr;
		curr = curr->al_next;
	}

	new_head->al_next = curr;
	new_head->al_prev = prev;

	if (curr == ald->al_ltop) {
		ald->al_ltop = new_head;
	} else {
		prev->al_next = new_head;
	}

	if (curr == 0) {
		ald->al_lbottom = new_head;
	} else {
		curr->al_prev = new_head;
	}

	ald->al_nelem++;
	return((void *) new_char);
}
