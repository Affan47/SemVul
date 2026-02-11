mpp_divis(mp_int *a, mp_int *b)
{
  mp_err  res;
  mp_int  rem;

  if((res = mp_init(&rem)) != MP_OKAY)
    return res;

  if((res = mp_mod(a, b, &rem)) != MP_OKAY)
    goto CLEANUP;

  if(mp_cmp_z(&rem) == 0)
    res = MP_YES;
  else
    res = MP_NO;

CLEANUP:
  mp_clear(&rem);
  return res;

}
