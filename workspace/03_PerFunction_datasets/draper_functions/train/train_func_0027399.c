mpp_fermat(mp_int *a, mp_digit w)
{
  mp_int  base, test;
  mp_err  res;

  if((res = mp_init(&base)) != MP_OKAY)
    return res;

  mp_set(&base, w);

  if((res = mp_init(&test)) != MP_OKAY)
    goto TEST;


  if((res = mp_exptmod(&base, a, a, &test)) != MP_OKAY)
    goto CLEANUP;


  if(mp_cmp(&base, &test) == 0)
    res = MP_YES;
  else
    res = MP_NO;

 CLEANUP:
  mp_clear(&test);
 TEST:
  mp_clear(&base);

  return res;

}
