InitializeWith(size_t siz,void *p)
{
	BitString *result = Create(CHAR_BIT*siz);
    if (result == NULL) {
        iError.RaiseError("iBitString.InitializeWith",CONTAINER_ERROR_NOMEMORY);
        return NULL;
    }
	memcpy(result->contents,p,siz);
	result->count = CHAR_BIT*siz;
	return result;
}
