UArray_pathExtension(UArray *self)
{
	long pos = UArray_findPathExtension(self);

	if (pos == -1 || pos == self->size - 1)
	{
		return UArray_newWithCString_copy_("", 1);
	}

	return UArray_range(self, pos + 1, self->size - pos - 1);
}
