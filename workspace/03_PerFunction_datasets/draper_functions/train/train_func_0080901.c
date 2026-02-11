main(void) {
    name_t **list = NULL;
    name_t *n = NULL;
    size_t list_len = 0;
    size_t list_maxlen = 0;
    size_t i;
    unsigned long long sum = 0;
    FILE *fd = fopen("names.txt", "r");
    if (!fd) {
	perror("main");
	return 1;
    }
    n = get_name(fd);
    while(n) {
	list_len++;
	if (list_len > list_maxlen) {
	    list_maxlen += 100;
	    list = realloc(list, list_maxlen*sizeof(name_t*));
	    if (!list) {
		perror("main");
		return 1;
	    }
	}
	list[list_len-1] = n;
	n = get_name(fd);
    }
    qsort(list, list_len, sizeof(name_t*), cmp);
    for (i = 0; i < 10; i ++) {
    }
    for (i = 0; i < list_len; i++) {
	sum += (list[i]->score * (i+1));
    }
    printf("%lld\n", sum);
    return 0;
}
