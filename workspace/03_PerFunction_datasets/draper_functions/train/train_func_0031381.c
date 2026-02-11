imag(struct value *val)
{
    switch (val->type) {
    case INTGR:
	return (0.0);
    case CMPLX:
	return (val->v.cmplx_val.imag);
    case STRING:


	int_warn(NO_CARET, "encountered a string when expecting a number");
	int_error(NO_CARET, "Did you try to generate a file name using dummy variable x or y?");
    default:
	int_error(NO_CARET, "unknown type in imag()");
    }

    return ((double) 0.0);
}
