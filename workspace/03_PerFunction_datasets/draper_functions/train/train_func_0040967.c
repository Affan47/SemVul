UArray_removeEvenIndexes(UArray *self)
{
	size_t itemSize = self->itemSize;
	size_t di = 0;
	size_t si = 1;
	size_t max = self->size;
	uint8_t *b = self->data;

	while (si < max)
	{
		uint8_t *src  = b + (si * itemSize);
		uint8_t *dest = b + (di * itemSize);
		memcpy(dest, src, itemSize);
		si = si + 2;
		di = di + 1;
	}

	UArray_setSize_(self, di);
}
