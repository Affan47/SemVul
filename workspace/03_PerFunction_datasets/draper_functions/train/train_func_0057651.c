d(char x) const {
		auto ix = memo.find(const_cast<memo_expr* const>(this));
		if ( ix == memo.end() ) {

			ptr<expr> dx = deriv(x);
			memo.insert(ix, std::make_pair(const_cast<memo_expr* const>(this), dx));
			return dx;
		} else {

			return ix->second;
		}
	}
