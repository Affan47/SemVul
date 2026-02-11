i2d_AC_TARGET(AC_TARGET *a, unsigned char **pp)
{
  int v1=0, v2=0, v3=0;

  M_ASN1_I2D_vars(a);
  M_ASN1_I2D_len_EXP_opt(a->name, i2d_GENERAL_NAME, 0, v1);
  M_ASN1_I2D_len_EXP_opt(a->group, i2d_GENERAL_NAME, 1, v2);
  M_ASN1_I2D_len_EXP_opt(a->cert, i2d_AC_IS, 2, v3);
  M_ASN1_I2D_seq_total();

  M_ASN1_I2D_put_EXP_opt(a->name, i2d_GENERAL_NAME, 0, v1);
  M_ASN1_I2D_put_EXP_opt(a->group, i2d_GENERAL_NAME, 1, v2);
  M_ASN1_I2D_put_EXP_opt(a->cert, i2d_AC_IS, 2, v3);
  M_ASN1_I2D_finish();
  return 0;
}
