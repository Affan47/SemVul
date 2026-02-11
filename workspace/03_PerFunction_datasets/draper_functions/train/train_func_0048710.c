d2i_AC_ATTRIBUTE(AC_ATTRIBUTE **a, SSLCONST unsigned char **pp, long length)
{
  M_ASN1_D2I_vars(a, AC_ATTRIBUTE *, AC_ATTRIBUTE_new);

  M_ASN1_D2I_Init();
  M_ASN1_D2I_start_sequence();
  M_ASN1_D2I_get(ret->name,      d2i_ASN1_OCTET_STRING);
  M_ASN1_D2I_get(ret->value,     d2i_ASN1_OCTET_STRING);
  M_ASN1_D2I_get(ret->qualifier, d2i_ASN1_OCTET_STRING);

  M_ASN1_D2I_Finish(a, AC_ATTRIBUTE_free, AC_F_D2I_AC_ATTRIBUTE);
}
