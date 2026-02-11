d2i_AC_HOLDER(AC_HOLDER **a, SSLCONST unsigned char **pp, long length)
{
  M_ASN1_D2I_vars(a, AC_HOLDER *, AC_HOLDER_new);

  M_ASN1_D2I_Init();
  M_ASN1_D2I_start_sequence();
  M_ASN1_D2I_get_IMP_opt(ret->baseid, d2i_AC_IS, 0, V_ASN1_SEQUENCE);
  M_ASN1_D2I_get_IMP_opt(ret->name, d2i_GENERAL_NAMES, 1, V_ASN1_SEQUENCE);
  M_ASN1_D2I_get_IMP_opt(ret->digest, d2i_AC_DIGEST, 2, V_ASN1_SEQUENCE);
  M_ASN1_D2I_Finish(a, AC_HOLDER_free, ASN1_F_D2I_AC_HOLDER);
}
