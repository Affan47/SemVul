IoState_symbolWithUArray_copy_(IoState *self, UArray *ba, int copy)
{
	IoSymbol *ioSymbol = SHash_at_(self->symbols, ba);

	if (!ioSymbol)
	{
		ioSymbol = IoSeq_newSymbolWithUArray_copy_(self, ba, copy);
		return IoState_addSymbol_(self, ioSymbol);
	}

	if (!copy)
	{
		UArray_free(ba);
	}

	IoState_stackRetain_(self, ioSymbol);
	return ioSymbol;
}
