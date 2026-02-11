dico_iterator_first(dico_iterator_t ip)
{
    if (!ip)
	return NULL;
    ip->cur = ip->list->head;
    ip->advanced = 0;
    ip->pos = 0;
    return dico_iterator_current(ip);
}
