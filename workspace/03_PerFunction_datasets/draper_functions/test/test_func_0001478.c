is_there(struct in_addr *t) {
    target_t	*c;

    if ((c=anchor)==NULL) return 0;
    while (c!=NULL) {
	if (memcmp(&(c->addr),t,4)==0) return 1;
	c=c->next;
    }
    return 0;
}
