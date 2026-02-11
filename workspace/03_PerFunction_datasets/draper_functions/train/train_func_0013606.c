read_mpc (FILE *fp, mpc_ptr z, known_signs_t *ks)
{
  read_mpfr (fp, mpc_realref (z), ks == NULL ? NULL : &ks->re);
  read_mpfr (fp, mpc_imagref (z), ks == NULL ? NULL : &ks->im);
}
