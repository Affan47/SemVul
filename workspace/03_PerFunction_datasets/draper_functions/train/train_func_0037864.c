i2d_AC_IETFATTR(AC_IETFATTR *a, unsigned char **pp)
{
  M_ASN1_I2D_vars(a);
  M_ASN1_I2D_len_IMP_opt(a->names, i2d_GENERAL_NAMES);
#if (OPENSSL_VERSION_NUMBER >= 0x10000000L)
  M_ASN1_I2D_len_SEQUENCE_type(AC_IETFATTRVAL, a->values, i2d_AC_IETFATTRVAL);
#elif (OPENSSL_VERSION_NUMBER >= 0x0090800fL)
  M_ASN1_I2D_len_SEQUENCE_type(AC_IETFATTRVAL, a->values, (int (*)(void*, unsigned char**))i2d_AC_IETFATTRVAL);
#else
  M_ASN1_I2D_len_SEQUENCE(a->values,  (int (*)())i2d_AC_IETFATTRVAL);
#endif
  M_ASN1_I2D_seq_total();

  M_ASN1_I2D_put_IMP_opt(a->names, i2d_GENERAL_NAMES, 0);
#if (OPENSSL_VERSION_NUMBER >= 0x10000000L)
  M_ASN1_I2D_put_SEQUENCE_type(AC_IETFATTRVAL, a->values, i2d_AC_IETFATTRVAL);
#elif (OPENSSL_VERSION_NUMBER >= 0x0090800fL)
  M_ASN1_I2D_put_SEQUENCE_type(AC_IETFATTRVAL, a->values, (int (*)(void*, unsigned char**))i2d_AC_IETFATTRVAL);
#else
  M_ASN1_I2D_put_SEQUENCE(a->values,  (int (*)())i2d_AC_IETFATTRVAL);
#endif
  M_ASN1_I2D_finish();
  return 0;
}
