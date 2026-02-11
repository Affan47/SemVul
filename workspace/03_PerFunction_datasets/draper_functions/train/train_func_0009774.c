RemoveSeries(TElement* equiv, TElement* e1, TElement* e2) {
    TNode* n1lb, *n2lb, *n2rt;
    TNode eqlb(BottomLeft, equiv);
    TNode eqrt(TopRight, equiv);

    Nodes(e2, n2lb, n2rt);
    n1lb = OtherNode(e1, n2lb);
    if (n1lb == nil) {
	n1lb = n2rt;
    } else if (n2rt == nil) {
	n2rt = n1lb;
    }
    n1lb->Merge(&eqlb);
    n2rt->Merge(&eqrt);
    n1lb->Exclude(e1);
    n2rt->Exclude(e2);
    Delete(n2lb);
    delete n2lb;
}
