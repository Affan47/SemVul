promote(type)
struct typestruct *type;
{
    scalar_t scalar;

    if ((scalar = type->scalar) & (CHAR | SHORT))
    {
	if (scalar & UNSIGNED)
	    return uitype;
	return itype;
    }
    if (scalar & FLOAT)
	return dtype;
    if (type->constructor & ARRAY)
	return pointype(type->nexttype);
    if (type->constructor & FUNCTION)
	return pointype(type);
    return type;
}
