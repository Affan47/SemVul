_hx509_private_key_ref(hx509_private_key key)
{
    if (key->ref == 0)
	_hx509_abort("key refcount <= 0 on ref");
    key->ref++;
    if (key->ref == UINT_MAX)
	_hx509_abort("key refcount == UINT_MAX on ref");
    return key;
}
