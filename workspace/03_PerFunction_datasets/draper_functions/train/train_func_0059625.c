LeadingAny(Node *p) {
	if (p == NULL) return NULL;
	Node *a = NULL;
	if (p->typ == Node::any) a = p;
	else if (p->typ == Node::alt) {
		a = LeadingAny(p->sub);
		if (a == NULL) a = LeadingAny(p->down);
	}
	else if (p->typ == Node::opt || p->typ == Node::iter) a = LeadingAny(p->sub);
	if (a == NULL && DelNode(p) && !p->up) a = LeadingAny(p->next);
	return a;
}
