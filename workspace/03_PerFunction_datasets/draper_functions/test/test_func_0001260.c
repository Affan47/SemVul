check_duplicate_override (Class *c, Method *method)
{
	GList *li;
	for (li = c->nodes; li != NULL; li = li->next) {
		Node *n = li->data;
		Method *m = (Method *)n;
		if(n->type != METHOD_NODE ||
		   m->method != OVERRIDE_METHOD)
			continue;

		if(method == m ||
		   method->line_no > m->line_no ||
		   strcmp(m->id, method->id) != 0 ||
		   strcmp(m->otype, method->otype) != 0)
			continue;
		error_printf(GOB_ERROR, m->line_no,
			     "override '%s(%s)' redefined, "
			     "first defined on line %d",
			     m->id, m->otype, method->line_no);
	}
}
