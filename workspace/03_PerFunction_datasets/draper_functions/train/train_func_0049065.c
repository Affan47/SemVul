_dxf_ResetDisplayListHash(HashTable ht)
{
    DLHashP ptr;

    if (ht)
    {
	DXInitGetNextHashElement(ht);
	while (NULL != (ptr = (DLHashP)DXGetNextHashElement(ht)))
	    ptr->hit = 0;
    }
}
