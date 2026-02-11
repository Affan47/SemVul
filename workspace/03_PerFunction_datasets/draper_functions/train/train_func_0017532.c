parse_ec_identifier(chunk_t identifier)
{
	chunk_t oid = chunk_empty;

	if (chunk_equals(identifier, chunk_from_str("nistp256")))
	{
		oid = asn1_build_known_oid(OID_PRIME256V1);
	}
	else if (chunk_equals(identifier, chunk_from_str("nistp384")))
	{
		oid = asn1_build_known_oid(OID_SECT384R1);
	}
	else if (chunk_equals(identifier, chunk_from_str("nistp521")))
	{
		oid = asn1_build_known_oid(OID_SECT521R1);
	}
	else
	{
		char ascii[64];

		if (snprintf(ascii, sizeof(ascii), "%.*s", (int)identifier.len,
					 identifier.ptr) < sizeof(ascii))
		{
			oid = asn1_wrap(ASN1_OID, "m", asn1_oid_from_string(ascii));
		}
	}
	return oid;
}
