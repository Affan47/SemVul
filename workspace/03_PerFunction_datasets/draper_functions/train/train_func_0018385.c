cp_ph_key(void *in, int idx, void *dest)
{
  if (ph_key_sz==2) {
    phokey_t *pharr = (phokey_t *)in;
    in = &pharr[idx];
  } else
  if (ph_key_sz==4) {
    u_int32_t *pharr4 = (u_int32_t *)in;
    in = &pharr4[idx];
  } else {
    u_int64_t *pharr8 = (u_int64_t *)in;
    in = &pharr8[idx];
  }

  memcpy(dest, in, ph_key_sz);
}
