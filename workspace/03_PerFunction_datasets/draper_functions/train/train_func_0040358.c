hx509_name_binary(const hx509_name name, heim_octet_string *os)
{
    size_t size;
    int ret;

    ASN1_MALLOC_ENCODE(Name, os->data, os->length, &name->der_name, &size, ret);
    if (ret)
	return ret;
    if (os->length != size)
	_hx509_abort("internal ASN.1 encoder error");

    return 0;
}
