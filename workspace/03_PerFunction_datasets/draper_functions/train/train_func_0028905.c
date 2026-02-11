ReplaceAt(BitString *b,size_t idx,int newval)
{
	size_t bytepos,bitpos;

	if (idx >= b->count) {
		iError.RaiseError("ReplaceAt",CONTAINER_ERROR_INDEX,b,idx);
		return 0;

	}
	bytepos = (idx/CHAR_BIT);
	bitpos = idx&(CHAR_BIT-1);
	if (newval)		b->contents[bytepos] |= BitIndexMask[bitpos];
	else
		b->contents[bytepos] &= ~BitIndexMask[bitpos];
	return 1;
}
