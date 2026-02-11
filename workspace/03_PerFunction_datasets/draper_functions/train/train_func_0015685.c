p1get_const(FILE *infile, int type, struct Constblock **resultp)
#endif
{
    int status;
    unsigned long a;
    struct Constblock *result;

	if (type != TYCHAR) {
		*resultp = result = ALLOC(Constblock);
		result -> tag = TCONST;
		result -> vtype = type;
		}

    switch (type) {
	case TYINT1:
        case TYSHORT:
	case TYLONG:
	case TYLOGICAL:
	case TYLOGICAL1:
	case TYLOGICAL2:
	    status = p1getd (infile, &(result -> Const.ci));
	    break;
#ifndef NO_LONG_LONG
	case TYQUAD:
		status = p1getq(infile, &result->Const.cq);
		break;
#endif
	case TYREAL:
	case TYDREAL:
	    status = p1getf(infile, &result->Const.cds[0]);
	    result->vstg = 1;
	    break;
	case TYCOMPLEX:
	case TYDCOMPLEX:
	    status = p1getf(infile, &result->Const.cds[0]);
	    if (status && status != EOF)
		status = p1getf(infile, &result->Const.cds[1]);
	    result->vstg = 1;
	    break;
	case TYCHAR:
	    status = fscanf(infile, "%lx", &a);
	    *resultp = (struct Constblock *) a;
	    break;
	default:
	    erri ("p1get_const:  bad constant type '%d'", type);
	    status = 0;
	    break;
    }

    return status;
}
