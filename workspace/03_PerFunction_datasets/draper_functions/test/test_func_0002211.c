getStochasticChildren(Node *node, set<StochasticNode*> &sset)
{


    set<StochasticNode*> const *schildren = node->stochasticChildren();
    sset.insert(schildren->begin(), schildren->end());

    set<DeterministicNode*> const *dchildren = node->deterministicChildren();
    set<DeterministicNode*>::const_iterator p;
    for (p = dchildren->begin(); p != dchildren->end(); ++p) {
	getStochasticChildren(*p, sset);
    }
}
