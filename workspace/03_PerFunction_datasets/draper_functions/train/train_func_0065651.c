com_right(struct et_list *list, long code)
{
    struct et_list *p;
    for (p = list; p; p = p->next) {
	if (code >= p->table->base && code < p->table->base + p->table->n_msgs)
	    return p->table->msgs[code - p->table->base];
    }
    return NULL;
}
