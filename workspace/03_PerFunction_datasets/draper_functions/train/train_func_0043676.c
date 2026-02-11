addConstraint(const char* relOp, int rhs, uint32 var) {
	if (good()) {
		if (relOp != 0) {
			if (relOp[0] == '>') {
				assert(relOp[1] == '=');

				WeightConstraint::newWeightConstraint(ctx_, posLit(var), lhs_, rhs);
			}
			else {
				assert(relOp[0] == '=');


				WeightLitVec temp(lhs_);
				WeightConstraint::newWeightConstraint(ctx_, posLit(var), lhs_, rhs) &&
				WeightConstraint::newWeightConstraint(ctx_, negLit(var), temp, rhs+1);
			}
		}
		else {
			obj_.lits   = lhs_;
			obj_.adjust = rhs;
		}
	}
}
}
