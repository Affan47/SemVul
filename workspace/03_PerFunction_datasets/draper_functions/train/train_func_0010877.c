operator=(
  const ZDD& right)
{
    if (this == &right) return *this;
    if (right.node != 0) Cudd_Ref(right.node);
    if (node != 0) {
	Cudd_RecursiveDerefZdd(p->manager,node);
	if (p->verbose) {
	    cout << "ZDD dereferencing for node " << hex << long(node) <<
		" ref = " << node->ref << "\n";
	}
    }
    node = right.node;
    p = right.p;
    if (node != 0 && p->verbose) {
	cout << "ZDD assignment for node " << hex << long(node) <<
	    " ref = " << node->ref << "\n";
    }
    return *this;

}
