UArray_clear(UArray *self)
{
	UARRAY_FOREACHASSIGN(self, i, v, 0);
}
