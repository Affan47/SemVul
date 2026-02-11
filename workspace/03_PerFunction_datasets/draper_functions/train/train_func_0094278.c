isClosed(set<Node const *> const &ancestors,
		       ClosedFuncClass fc, bool fixed) const
{
    switch(fc) {
    case DNODE_SCALE:

	for (unsigned int i = 0; i < parents().size(); ++i) {
	    if (ancestors.count(parents()[i]) == 0) {
		return false;
	    }
	}
	break;
    case DNODE_SCALE_MIX:

	if (ancestors.count(parents()[0]) == 0)
	    return false;
	for (unsigned int i = 1; i < parents().size(); ++i) {
	    if (parents()[i] != parents()[0])
		return false;
	}
	break;
    case DNODE_LINEAR:
	break;
    case DNODE_POWER:
	return false;
	break;
    }
    return true;
}
