cleanup(void) {
    struct ignore_s *elem;
    int i;

    for (i = 0; i < output.limit; ++i) {
	free(output.array[i]);
    }
    free(output.array);

    elem = ignore_list;
    while (elem) {
	struct ignore_s *next = elem->next;
	regfree(&elem->regex);
	free(elem->patt);
	free(elem);
	elem = next;
    }
}
