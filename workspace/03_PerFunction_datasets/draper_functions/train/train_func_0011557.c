ossl_rand_egd_bytes(VALUE self, VALUE filename, VALUE len)
{
    int n = NUM2INT(len);

    SafeStringValue(filename);

    if (!RAND_egd_bytes(RSTRING_PTR(filename), n)) {
	ossl_raise(eRandomError, NULL);
    }
    return Qtrue;
}
