nodeValues(GraphView const *gv, unsigned int chain)
{
    vector<double> ans(gv->length());
    gv->getValue(ans, chain);

    StochasticNode const *dchild = getDSumNode(gv);
    if (!dchild) {
	throwLogicError("DSum Child not found in RWDSum method");
    }


    bool discrete = dchild->isDiscreteValued();
    for (unsigned int i = 0; i < gv->nodes().size(); ++i) {
	if (gv->nodes()[i]->isDiscreteValued() != discrete) {
	    throwLogicError("Discrete value inconsistency in RWDSum method");
	}
    }


    if (discrete) {
	for (unsigned int i = 0; i < ans.size(); ++i) {
	    ans[i] = static_cast<int>(ans[i]);
	}
    }


    unsigned int nrow = dchild->length();
    unsigned int ncol = gv->nodes().size();

    if (ans.size() != nrow * ncol) {
	throwLogicError("Inconsistent lengths in RWDSum method");
    }

    for (unsigned int r = 0; r < nrow; ++r) {

	double delta = dchild->value(chain)[r];
	for (unsigned int c = 0; c < ncol; ++c) {
	    delta -= ans[c * nrow + r];
	}

	if (delta != 0) {
	    if (discrete) {
		int idelta = static_cast<int>(delta);
		if (delta != idelta) {
		    throwLogicError("Unable to satisfy dsum constraint");
		}
		int eps = idelta / ncol;
		int resid = idelta % ncol;

		for (unsigned int c = 0; c < ncol; ++c) {
		    ans[c * nrow + r] += eps;
		}
		ans[r] += resid;
	    }
	    else {
		double eps = delta / ncol;
		for (unsigned int c = 0; c < ncol; ++c) {
		    ans[c * nrow + r] += eps;
		}
	    }
	}
    }

    gv->setValue(ans, chain);
    return(ans);
}
