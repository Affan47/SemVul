UArray_equalsAnyCase_(const UArray *self, const UArray *other)
{
	if (self->size == other->size)
	{
		return UArray_findAnyCase_(self, other) == 0;
	}

	return 0;
}
