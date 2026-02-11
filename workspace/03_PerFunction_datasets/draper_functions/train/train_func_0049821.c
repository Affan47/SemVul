insertNode(list l, msg mess)
{
    node new;

    new = G_malloc(sizeof(struct nodoLista));
    new->m = G_malloc(sizeof(msg));

    if (new != NULL) {
	memcpy(new->m, &mess, sizeof(msg));
	new->next = new->prev = NULL;

	if (l->head == NULL) {
	    l->head = l->tail = new;
	}
	else {
	    l->tail->next = new;
	    new->prev = l->tail;
	    l->tail = new;
	}
    }
    else
	G_message(_("Out of memory"));

    l->size++;
}
