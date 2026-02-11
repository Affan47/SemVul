f_ne(union argument *arg)
{
    struct value a, b;
    int result = 0;

    (void) arg;
    (void) pop(&b);
    (void) pop(&a);
    switch (a.type) {
    case INTGR:
	switch (b.type) {
	case INTGR:
	    result = (a.v.int_val !=
		      b.v.int_val);
	    break;
	case CMPLX:
	    result = (a.v.int_val !=
		      b.v.cmplx_val.real ||
		      b.v.cmplx_val.imag != 0.0);
	    break;
	    BAD_DEFAULT
	}
	break;
    case CMPLX:
	switch (b.type) {
	case INTGR:
	    result = (b.v.int_val !=
		      a.v.cmplx_val.real ||
		      a.v.cmplx_val.imag != 0.0);
	    break;
	case CMPLX:
	    result = (a.v.cmplx_val.real !=
		      b.v.cmplx_val.real ||
		      a.v.cmplx_val.imag !=
		      b.v.cmplx_val.imag);
	    break;
	    BAD_DEFAULT
	}
	break;
	BAD_DEFAULT
    }
    push(Ginteger(&a, result));
}
