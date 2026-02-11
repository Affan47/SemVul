checkOutcome(StochasticNode const *snode,
				   LinkNode const *lnode) const
    {
	GLMFamily family = GLMMethod::getFamily(snode);
	if (family == GLM_NORMAL) {
	    return lnode == 0;
	}
	else if (!lnode) {
	    return false;
	}
	else {
	    string link = lnode->linkName();
	    switch(family) {
	    case GLM_BERNOULLI: case GLM_BINOMIAL:
		return link == "probit" || link == "logit";
	    case GLM_POISSON:
		return link == "log";
	    case GLM_UNKNOWN: case GLM_NORMAL:
		return false;
	    }
	}
	return false;
    }
