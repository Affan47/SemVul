common_crypt (char *key, char *buf, register unsigned len,
	      unsigned mode, register struct desparams *desp)
{
  register int desdev;

  if ((len % 8) != 0 || len > DES_MAXDATA)
    return DESERR_BADPARAM;

  desp->des_dir =
    ((mode & DES_DIRMASK) == DES_ENCRYPT) ? ENCRYPT : DECRYPT;

  desdev = mode & DES_DEVMASK;
  COPY8 (key, desp->des_key);


  if (!_des_crypt (buf, len, desp))
    return DESERR_HWERROR;

  return desdev == DES_SW ? DESERR_NONE : DESERR_NOHWDEVICE;
}
