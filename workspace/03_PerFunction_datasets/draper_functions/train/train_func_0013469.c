ParseDoOp(int op)
{
	GNode	*cohort;
	LstNode	*ln;
	GNode	*gn;

	LST_FOREACH(ln, &targets) {
		gn = Lst_Datum(ln);


		if ((op & OP_OPMASK) != (gn->type & OP_OPMASK) &&
		    !OP_NOP(gn->type) && !OP_NOP(op)) {
			Parse_Error(PARSE_FATAL, "Inconsistent operator for %s",
			    gn->name);
			return;
		}

		if (op == OP_DOUBLEDEP &&
		    (gn->type & OP_OPMASK) == OP_DOUBLEDEP) {


			cohort = Targ_NewGN(gn->name);


			ParseLinkSrc(&gn->parents, cohort);
			cohort->type = OP_DOUBLEDEP|OP_INVISIBLE;
			Lst_AtEnd(&gn->cohorts, cohort);


			Lst_Replace(ln, cohort);
			gn = cohort;
		}


		gn->type |= op;
	}
}
