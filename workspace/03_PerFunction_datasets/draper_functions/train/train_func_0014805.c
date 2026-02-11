R_type_to_gretl_type (SEXP s)
{
    if (R_isMatrix(s)) {
	return GRETL_TYPE_MATRIX;
    } else if (R_isLogical(s)) {
	return GRETL_TYPE_BOOL;
    } else if (R_isInteger(s)) {
	return GRETL_TYPE_INT;
    } else if (R_isReal(s)) {
	return GRETL_TYPE_DOUBLE;
    } else {
	return GRETL_TYPE_NONE;
    }
}
