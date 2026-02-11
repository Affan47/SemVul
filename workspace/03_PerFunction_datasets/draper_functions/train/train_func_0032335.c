getLeftNeighbours(NodeSet &scanline,Node *v) {
	NodeSet *leftv = new NodeSet;
	NodeSet::iterator i=scanline.find(v);
	while(i--!=scanline.begin()) {
		Node *u=*(i);
		if(u->r->overlapX(v->r)<=0) {
			leftv->insert(u);
			return leftv;
		}
		if(u->r->overlapX(v->r)<=u->r->overlapY(v->r)) {
			leftv->insert(u);
		}
	}
	return leftv;
}
