MarkReachedNts(Node *p) {
	while (p != NULL) {
		if (p->typ == Node::nt && !((*visited)[p->sym->n])) {
			visited->Set(p->sym->n, true);
			MarkReachedNts(p->sym->graph);
		} else if (p->typ == Node::alt || p->typ == Node::iter || p->typ == Node::opt) {
			MarkReachedNts(p->sub);
			if (p->typ == Node::alt) MarkReachedNts(p->down);
		}
		if (p->up) break;
		p = p->next;
	}
}
