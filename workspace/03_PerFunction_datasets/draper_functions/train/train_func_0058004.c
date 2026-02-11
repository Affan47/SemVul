list_mknode(void)
{
	struct list *tmp = NULL;

	tmp = malloc(sizeof(struct list));
	if (NULL == tmp) {
		fprintf(stderr, "%s:%d malloc error.\n",
			__func__, __LINE__);
		exit(1);
	}
	tmp->next = NULL;

	return tmp;
}
