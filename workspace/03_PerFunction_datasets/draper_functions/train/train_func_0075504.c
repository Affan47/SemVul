find_func(name)
    char_u	*name;
{
    hashitem_T	*hi;

    hi = hash_find(&func_hashtab, name);
    if (!HASHITEM_EMPTY(hi))
	return HI2UF(hi);
    return NULL;
}
