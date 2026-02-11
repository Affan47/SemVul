IoObject_defaultCompare(IoObject *self, IoObject *v)
{


	ptrdiff_t d = -((ptrdiff_t)IoObject_tag(self) - (ptrdiff_t)IoObject_tag(v));


	if (d == 0)
	{
		d = ((ptrdiff_t)self) - ((ptrdiff_t)v);
	}

	if (d == 0) return 0;

	return d > 0 ? 1 : -1;
}
