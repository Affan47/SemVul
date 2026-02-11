s_net_find(NET * net_head, NET * node)
{
    NET *n_current;

    n_current = net_head;
    while (n_current != NULL) {
	if (n_current->nid == node->nid) {
	    return (TRUE);
	}

	n_current = n_current->next;
    }
    return (FALSE);
}
