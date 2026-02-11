sync_action_list_add(struct sync_action_list *l, char *name, char *user)
{
    struct sync_action *current;

    if (!name && !user) return;

    for (current = l->head ; current ; current = current->next) {
        if ((!name || (current->name && !strcmp(current->name, name))) &&
	    (!user || (current->user && !strcmp(current->user, user)))) {
	    current->active = 1;
	    return;
	} else {

	}
    }

    current           = xzmalloc(sizeof(struct sync_action));
    current->next     = NULL;
    current->name     = (name)  ? xstrdup(name)  : NULL;
    current->user     = (user)  ? xstrdup(user)  : NULL;
    current->active   = 1;

    if (l->tail)
        l->tail = l->tail->next = current;
    else
        l->head = l->tail = current;

    l->count++;

}
