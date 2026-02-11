count_destructors (Class *c)
{
	int num = 0;
	GList *li;
	for (li = c->nodes; li != NULL; li = li->next) {
		Node *n = li->data;
		if (n->type == VARIABLE_NODE) {
			Variable *v = (Variable *)n;
			if (v->destructor != NULL &&
			    ! v->destructor_unref &&
			    v->scope != CLASS_SCOPE)
				num++;
		}
	}
	return num;
}
