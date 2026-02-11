build_requestorName(private_x509_ocsp_request_t *this)
{
	if (this->requestor || this->cert)
	{
		if (!this->requestor)
		{
			this->requestor = this->cert->get_subject(this->cert);
			this->requestor = this->requestor->clone(this->requestor);
		}
		return asn1_wrap(ASN1_CONTEXT_C_1, "m",
					asn1_simple_object(ASN1_CONTEXT_C_4,
						this->requestor->get_encoding(this->requestor)));

	}
	return chunk_empty;
}
