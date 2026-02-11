i2d_AC_VAL(AC_VAL *a, unsigned char **pp)
{
  M_ASN1_I2D_vars(a);

  M_ASN1_I2D_len(a->notBefore, i2d_ASN1_GENERALIZEDTIME);
  M_ASN1_I2D_len(a->notAfter,  i2d_ASN1_GENERALIZEDTIME);

  M_ASN1_I2D_seq_total();

  M_ASN1_I2D_put(a->notBefore, i2d_ASN1_GENERALIZEDTIME);
  M_ASN1_I2D_put(a->notAfter,  i2d_ASN1_GENERALIZEDTIME);

  M_ASN1_I2D_finish();
  return 0;
}
