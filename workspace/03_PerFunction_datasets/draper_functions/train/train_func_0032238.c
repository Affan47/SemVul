ECIES_decryption(char *key, const struct affine_point *R,
		     const gcry_mpi_t d, const struct curve_params *cp)
{
  struct affine_point Z;
  gcry_mpi_t e;
  int res = 0;
  if (! embedded_key_validation(R, &cp->dp))
    return 0;
  e = gcry_mpi_snew(0);
  gcry_mpi_mul_ui(e, d, cp->dp.cofactor);
  Z = pointmul(R, e, &cp->dp);
  gcry_mpi_release(e);
  if ((res = ! point_is_zero(&Z)))
    ECIES_KDF(key, Z.x, R, cp->elem_len_bin);
  point_release(&Z);
  return res;
}
