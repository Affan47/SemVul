count_get_arguments(Class *c)
{
	int num = 0;
	GList *li;
	for(li = c->nodes; li != NULL; li = li->next) {
		Node *n = li->data;
		Argument *a = li->data;
		if(n->type == ARGUMENT_NODE &&
		   a->get)
			num ++;
	}
	return num;
}
