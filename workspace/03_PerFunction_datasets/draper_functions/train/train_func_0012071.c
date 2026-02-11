GetRange(BitString *bs,size_t start,size_t end)
{
	size_t len;
	BitString *result;
	size_t startbyte,endbyte,shiftamount,bytesToCopy,idx;

	if (bs == NULL || start >=bs->count || start > end) {
		NullPtrError("GetRange");
		return NULL;
	}
	if (end >= bs->count)
		end = bs->count;
	len  = end-start;
	result = Create(len);
    if (result == NULL) {
        iError.RaiseError("iBitString.GetRange",CONTAINER_ERROR_NOMEMORY);
        return NULL;
    }
	if (len == 0)
		return result;
	result->count = len;
	startbyte = start/CHAR_BIT;
	endbyte = end/CHAR_BIT;
	shiftamount = start&(CHAR_BIT-1);
	if (shiftamount == 0) {

		memmove(result->contents,bs->contents+startbyte,1+endbyte-startbyte);
	}
	else {


		result->contents[0] = (bs->contents[startbyte] >> shiftamount);
		bytesToCopy = (endbyte-startbyte);
		idx = 1;
		while (bytesToCopy) {


			unsigned b = (bs->contents[++startbyte] << (CHAR_BIT-shiftamount));
			result->contents[idx-1] |= b;

			b = (bs->contents[startbyte] >> shiftamount);
			result->contents[idx] |= b;
			bytesToCopy--;
			idx++;
		}
	}
	return result;
}
