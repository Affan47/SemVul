CheckAlts(Node *p) {
	BitArray *s1, *s2;
	while (p != NULL) {
		if (p->typ == Node::alt) {
			Node *q = p;
			s1 = new BitArray(terminals->Count);
			while (q != NULL) {
				s2 = Expected0(q->sub, curSy);
				CheckOverlap(s1, s2, 1);
				s1->Or(s2);
				CheckAlts(q->sub);
				q = q->down;
			}
		} else if (p->typ == Node::opt || p->typ == Node::iter) {
			if (DelSubGraph(p->sub)) LL1Error(4, NULL);
			else {
				s1 = Expected0(p->sub, curSy);
				s2 = Expected(p->next, curSy);
				CheckOverlap(s1, s2, 2);
			}
			CheckAlts(p->sub);
		} else if (p->typ == Node::any) {
			if (Sets::Elements(p->set) == 0) LL1Error(3, NULL);

		}
		if (p->up) break;
		p = p->next;
	}
}
