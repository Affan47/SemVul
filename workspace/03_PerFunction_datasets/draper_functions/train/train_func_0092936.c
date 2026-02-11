_gnutls_decode_ber_rs (const gnutls_datum_t * sig_value, bigint_t * r,
                       bigint_t * s)
{
  ASN1_TYPE sig;
  int result;

  if ((result =
       asn1_create_element (_gnutls_get_gnutls_asn (),
                            "GNUTLS.DSASignatureValue",
                            &sig)) != ASN1_SUCCESS)
    {
      gnutls_assert ();
      return _gnutls_asn2err (result);
    }

  result = asn1_der_decoding (&sig, sig_value->data, sig_value->size, NULL);
  if (result != ASN1_SUCCESS)
    {
      gnutls_assert ();
      asn1_delete_structure (&sig);
      return _gnutls_asn2err (result);
    }

  result = _gnutls_x509_read_int (sig, "r", r);
  if (result < 0)
    {
      gnutls_assert ();
      asn1_delete_structure (&sig);
      return result;
    }

  result = _gnutls_x509_read_int (sig, "s", s);
  if (result < 0)
    {
      gnutls_assert ();
      _gnutls_mpi_release (s);
      asn1_delete_structure (&sig);
      return result;
    }

  asn1_delete_structure (&sig);

  return 0;
}
