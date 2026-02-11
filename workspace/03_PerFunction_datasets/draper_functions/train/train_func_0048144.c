index_thread_sort(Thread *root, struct sortcrit *sortcrit)
{
    Thread *child;


    child = root->child;
    while (child) {

	if (child->child)
	    index_thread_sort(child, sortcrit);
	child = child->next;
    }


    root->child = lsort(root->child,
			(void * (*)(void*)) index_thread_getnext,
			(void (*)(void*,void*)) index_thread_setnext,
			(int (*)(void*,void*,void*)) index_thread_compare,
			sortcrit);
}
