AddMissingNodes(TElement* e) {
    TNode* nlb, *nrt;
    TNodeList* lb, *rt;

    Nodes(e, nlb, nrt);
    if (nlb == nil) {
	nlb = new TNode(BottomLeft, e);
	nlb->SetPosition(e->pos);
	lb = new TNodeList(nlb);
	Append(lb);

    }
    if (nrt == nil) {
	nrt = new TNode(TopRight, e);
	nrt->SetPosition(e->pos + e->nat + e->sigma);
	rt = new TNodeList(nrt);
	Append(rt);
    }
}
