i2d_AC_HOLDER(AC_HOLDER *a, unsigned char **pp)
{
  M_ASN1_I2D_vars(a);

  M_ASN1_I2D_len_IMP_opt(a->baseid, i2d_AC_IS);
  M_ASN1_I2D_len_IMP_opt(a->name, i2d_GENERAL_NAMES);
  M_ASN1_I2D_len_IMP_opt(a->digest, i2d_AC_DIGEST);
  M_ASN1_I2D_seq_total();

  M_ASN1_I2D_put_IMP_opt(a->baseid, i2d_AC_IS, 0);
  M_ASN1_I2D_put_IMP_opt(a->name, i2d_GENERAL_NAMES, 1);
  M_ASN1_I2D_put_IMP_opt(a->digest, i2d_AC_DIGEST, 2);
  M_ASN1_I2D_finish();
  return 0;
}
