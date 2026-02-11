mp_clear (mp_int * a)
{
  int i;


  if (a->dp != NULL) {

    for (i = 0; i < a->used; i++) {
        a->dp[i] = 0;
    }


    XFREE(a->dp);


    a->dp    = NULL;
    a->alloc = a->used = 0;
    a->sign  = MP_ZPOS;
  }
}
