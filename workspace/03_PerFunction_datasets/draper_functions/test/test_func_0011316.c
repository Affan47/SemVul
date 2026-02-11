ref_sort_root(Thread *root)
{
    Thread *cur;
    struct sortcrit sortcrit[] = {{ SORT_DATE,     0, {{NULL, NULL}} },
				  { SORT_SEQUENCE, 0, {{NULL, NULL}} }};

    cur = root->child;
    while (cur) {

	if (!cur->msgdata) {
	    cur->child = lsort(cur->child,
			       (void * (*)(void*)) index_thread_getnext,
			       (void (*)(void*,void*)) index_thread_setnext,
			       (int (*)(void*,void*,void*)) index_thread_compare,
			       sortcrit);
	}
	cur = cur->next;
    }


    root->child = lsort(root->child,
			(void * (*)(void*)) index_thread_getnext,
			(void (*)(void*,void*)) index_thread_setnext,
			(int (*)(void*,void*,void*)) index_thread_compare,
			sortcrit);
}
