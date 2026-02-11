addPredecessorClauses(SharedContext& ctx, ClauseCreator& gc, const AtomList& prgAtoms) {
	const Literal negBody = ~literal();
	ClauseCreator bc(ctx.master());
	gc.start().add(literal());
	bool sat = false;
	for (Literal* it = goals_, *end = goals_+size_; it != end; ++it) {
		assert(it->var() != 0);
		Literal aEq = it->sign() ? ~prgAtoms[it->var()]->literal() : prgAtoms[it->var()]->literal();
		if (negBody != ~aEq) {
			bc.start().add(negBody);
			if ( (negBody != aEq && !bc.add(aEq).end()) || (negBody == aEq && !bc.end()) ) {
				return false;
			}
		}
		sat |= aEq == literal();
		if (~aEq != literal()) {
			gc.add( ~aEq );
		}
	}
	return sat || gc.end();
}
