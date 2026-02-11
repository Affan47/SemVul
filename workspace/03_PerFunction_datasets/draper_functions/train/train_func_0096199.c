check_duplicate (Class *c, Node *node, const char *id, int line_no)
{
	GList *li;
	for (li = c->nodes; li != NULL; li = li->next) {
		Node *n = li->data;
		const char *nid;
		int nline_no;
		if(n->type == METHOD_NODE) {
			Method *m = (Method *)n;


			if(m->method == OVERRIDE_METHOD)
				continue;

			nid = m->id;
			nline_no = m->line_no;
		} else if(n->type == VARIABLE_NODE) {
			Variable *v = (Variable *)n;
			nid = v->id;
			nline_no = v->line_no;
		} else
			continue;
		if(n == node ||
		   line_no > nline_no ||
		   n->type != node->type ||
		   strcmp(nid, id) != 0)
			continue;

		error_printf (GOB_ERROR, nline_no,
			      "symbol '%s' redefined, "
			      "first defined on line %d",
			      id, line_no);
	}
}
