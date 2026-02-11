mp_clamp (mp_int * a)
{


  while (a->used > 0 && a->dp[a->used - 1] == 0) {
    --(a->used);
  }


  if (a->used == 0) {
    a->sign = MP_ZPOS;
  }
}
