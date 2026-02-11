UArray_bitwiseNot(UArray *self)
{
	size_t i, max = UArray_sizeInBytes(self);
	uint8_t *data = self->data;
	for (i = 0; i < max; i ++) { data[i] = ~(data[i]); }
}
