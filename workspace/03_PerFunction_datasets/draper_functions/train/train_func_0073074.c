i2d_AC_ACI(AC_ACI *a, unsigned char **pp)
{
  M_ASN1_I2D_vars(a);
  M_ASN1_I2D_len_IMP_opt(a->form, i2d_AC_FORM);
  M_ASN1_I2D_seq_total();

  M_ASN1_I2D_put_IMP_opt(a->form, i2d_AC_FORM, 0);
  M_ASN1_I2D_finish();
  return 0;
}
