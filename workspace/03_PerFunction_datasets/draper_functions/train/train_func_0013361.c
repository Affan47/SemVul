removeFromTail(Solver& s, Literal* it, Literal* end) {
	assert(it != end || contracted());
	if (!contracted()) {
		*it  = *--end;
		*end = negLit(0);
		if (!isSmall()) {
			data_.local.setSize(data_.local.size()-1);
			data_.local.idx = 0;
		}
	}
	else {
		uint32 uLev  = s.level(end->var());
		Literal* j   = it;
		while ( !j->watched() ) { *j++ = *++it; }
		*j           = negLit(0);
		uint32 nLev  = s.level(end->var());
		if (uLev != nLev && s.removeUndoWatch(uLev, this) && nLev != 0) {
			s.addUndoWatch(nLev, this);
		}
		if (j != end) { (j-1)->watch(); }
		else          { data_.local.clearContracted(); }
		end = j;
	}
	if (learnt() && !isSmall() && !strengthened()) {
		end->watch();
		data_.local.markStrengthened();
	}
	return end;
}
