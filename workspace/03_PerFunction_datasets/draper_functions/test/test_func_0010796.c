pp_list_find(struct grecs_list *list, struct file_data *dptr)
{
	struct grecs_list_entry *ep;

	for (ep = list->head; !dptr->found && ep; ep = ep->next) {
		const char *dir = ep->data;
		size_t size = strlen (dir) + 1 + dptr->namelen + 1;
		if (size > dptr->buflen) {
			dptr->buflen = size;
			dptr->buf = grecs_realloc(dptr->buf, dptr->buflen);
		}
		strcpy(dptr->buf, dir);
		strcat(dptr->buf, "/");
		strcat(dptr->buf, dptr->name);
		dptr->found = access(dptr->buf, F_OK) == 0;
	}
	return dptr->found;
}
