_hx509_verify_signature_bitstring(hx509_context context,
				  const hx509_cert signer,
				  const AlgorithmIdentifier *alg,
				  const heim_octet_string *data,
				  const heim_bit_string *sig)
{
    heim_octet_string os;

    if (sig->length & 7) {
	hx509_set_error_string(context, 0, HX509_CRYPTO_SIG_INVALID_FORMAT,
			       "signature not multiple of 8 bits");
	return HX509_CRYPTO_SIG_INVALID_FORMAT;
    }

    os.data = sig->data;
    os.length = sig->length / 8;

    return _hx509_verify_signature(context, signer, alg, data, &os);
}
