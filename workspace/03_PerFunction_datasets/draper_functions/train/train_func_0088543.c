rafineStrictInteger(const Theorem& isIntConstrThm, const Expr& constr) {


	if (CHECK_PROOFS) {

		CHECK_SOUND(isIneq(constr), "rafineStrictInteger: expected a constraint got : " + constr.toString());
		CHECK_SOUND(isIntConstrThm.getExpr()[0] == constr[1], "rafineStrictInteger: proof of intger doesn't correspond to the constarint right side");
		CHECK_SOUND(constr[0].isRational(), "rafineStrictInteger: right side of the constraint muts be a rational");
	}


	Rational bound = constr[0].getRational();


	int kind = constr.getKind();


	switch (kind) {
		case LT:
			kind = LE;
			if (bound.isInteger()) bound ++;
			else bound = ceil(bound);
			break;
		case LE:
			kind = LE;
			if (!bound.isInteger()) bound = ceil(bound);
			break;
		case GT:
			kind = GE;
			if (bound.isInteger()) bound --;
			else bound = floor(bound);
			break;
		case GE:
			kind = GE;
			if (!bound.isInteger()) bound = floor(bound);
			break;
	}


	Expr newConstr(kind, rat(bound), constr[1]);


	const Assumptions& assump(isIntConstrThm.getAssumptionsRef());


  	Proof pf;
	if (withProof()) pf = newPf("rafineStrictInteger", constr, newConstr,isIntConstrThm.getProof());


	return newRWTheorem(constr, newConstr, assump, pf);
}
