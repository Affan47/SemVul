PKCS7_stream(unsigned char ***boundary, PKCS7 *p7)
	{
	ASN1_OCTET_STRING *os = NULL;

	switch (OBJ_obj2nid(p7->type))
		{
		case NID_pkcs7_data:
		os = p7->d.data;
		break;

		case NID_pkcs7_signedAndEnveloped:
		os = p7->d.signed_and_enveloped->enc_data->enc_data;
		if (os == NULL)
			{
			os=M_ASN1_OCTET_STRING_new();
			p7->d.signed_and_enveloped->enc_data->enc_data=os;
			}
		break;

		case NID_pkcs7_enveloped:
		os = p7->d.enveloped->enc_data->enc_data;
		if (os == NULL)
			{
			os=M_ASN1_OCTET_STRING_new();
			p7->d.enveloped->enc_data->enc_data=os;
			}
		break;

		case NID_pkcs7_signed:
		os=p7->d.sign->contents->d.data;
		break;

		default:
		os = NULL;
		break;
		}

	if (os == NULL)
		return 0;

	os->flags |= ASN1_STRING_FLAG_NDEF;
	*boundary = &os->data;

	return 1;
	}
