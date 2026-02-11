zeroconst(expptr e)
#endif
{
	Constp c = (Constp) e;
	if (c->tag == TCONST)
		switch(c->vtype) {
		case TYINT1:
		case TYSHORT:
		case TYLONG:
#ifdef TYQUAD0
		case TYQUAD:
#endif
			return c->Const.ci == 0;
#ifndef NO_LONG_LONG
		case TYQUAD:
			return c->Const.cq == 0;
#endif

		case TYREAL:
		case TYDREAL:
			if (c->vstg == 1)
				return !strcmp(c->Const.cds[0],"0.");
			return c->Const.cd[0] == 0.;

		case TYCOMPLEX:
		case TYDCOMPLEX:
			if (c->vstg == 1)
				return !strcmp(c->Const.cds[0],"0.")
				    && !strcmp(c->Const.cds[1],"0.");
			return c->Const.cd[0] == 0. && c->Const.cd[1] == 0.;
		}
	return 0;
	}
