_ojc_val_cleanup() {
    ojcVal	v;
    ojcVal	head;
    Bstr	bhead;
    Bstr	b;

    pthread_mutex_lock(&free_mutex);
    head = free_vals.head;
    free_vals.head = 0;
    free_vals.tail = 0;
    bhead = free_bstrs.head;
    free_bstrs.head = 0;
    free_bstrs.tail = 0;
    pthread_mutex_unlock(&free_mutex);

    while (0 != head) {
	v = head;
	head = v->next;
	free(v);
    }

    while (0 != bhead) {
	b = bhead;
	bhead = b->next;
	free(b);
    }
}
