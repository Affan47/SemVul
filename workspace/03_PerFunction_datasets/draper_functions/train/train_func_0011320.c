UArray_logicalAnd_(UArray *self, const UArray *other)
{
	DUARRAY_INTOP(UARRAY_LOGICOP_TYPES, &&, self, other);
}
