UArray_beginsWith_(UArray *self, const UArray *other)
{
	int msize = self->size;
	int osize = other->size;

	if ((msize >= 0) && (msize >= osize))
	{


		if (osize == 1) {
			return (*(self->data) == *(other->data));
		}
		else if (memcmp(self->data, other->data, osize) == 0){
			return 1;
		}
		return 0;
	}
	return  0;
}
