txt2obj(const char *oid)
	{
	ASN1_OBJECT *oid_obj = NULL;

	if (!(oid_obj = OBJ_txt2obj(oid, 0)))
		BIO_printf(bio_err, "cannot convert %s to OID\n", oid);

	return oid_obj;
	}
