cmd_listjobs()
{
	if (ShowTokens) {
		PrintToken(LISTJOBS, "listjobs", "listjobs");
	}
	printf("listing currently running jobs\n");
	struct pidlist_t *newlist = NULL;
	struct pidlist_t *iter = bg_procs;
	struct pidlist_t *tmp = NULL;
	int length = 0;
	while (iter != NULL) {
		if (proc_running(iter->pid)) {
			printf("%d %s\n", iter->pid, iter->name);
			length++;
			struct pidlist_t *node = malloc(sizeof(struct pidlist_t));
			node->pid = iter->pid;
			node->name = iter->name;
			node->next = newlist;
			newlist = node;
		}
		iter = iter->next;
	}
	iter = bg_procs;
	while (iter != NULL) {
		tmp = iter->next;
		free(iter);
		iter = tmp;
	}
	bg_procs = newlist;
	printf("there are currently %d proccesses running\n", length);
}
