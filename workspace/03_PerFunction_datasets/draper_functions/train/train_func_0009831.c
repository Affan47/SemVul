findMix(GraphView const *gv)
{

    vector<DeterministicNode*> const &dchild = gv->deterministicChildren();
    for (unsigned int i = 0; i < dchild.size(); ++i) {
	if (isMixture(dchild[i])) return true;
    }
    return false;
}
