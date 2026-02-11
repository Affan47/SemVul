dict_destroy(dict *dct, int del)
{
	ASSERT(dct != NULL);

	dct->_destroy(dct->_object, del);
	FREE(dct);
}
