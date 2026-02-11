parse_safe_content(hx509_context context,
		   struct hx509_collector *c,
		   const unsigned char *p, size_t len)
{
    PKCS12_SafeContents sc;
    int ret;
    size_t i;

    memset(&sc, 0, sizeof(sc));

    ret = decode_PKCS12_SafeContents(p, len, &sc, NULL);
    if (ret)
	return ret;

    for (i = 0; i < sc.len ; i++)
	parse_pkcs12_type(context,
			  c,
			  &sc.val[i].bagId,
			  sc.val[i].bagValue.data,
			  sc.val[i].bagValue.length,
			  sc.val[i].bagAttributes);

    free_PKCS12_SafeContents(&sc);
    return 0;
}
