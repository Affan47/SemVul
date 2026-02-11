deriv(char x) const {

		memo[const_cast<rule_expr* const>(this)] = inf_expr::make();

		ptr<expr> rVal = r->d(x);

		memo.erase(const_cast<rule_expr* const>(this));
		return rVal;
	}
