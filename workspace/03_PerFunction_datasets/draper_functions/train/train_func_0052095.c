fp_sqr_comba(fp_int *A, fp_int *B)
{
  int       pa, ix, iz;
  fp_digit  c0, c1, c2;
  fp_int    tmp, *dst;
#ifdef TFM_ISO
  fp_word   tt;
#endif


  pa = A->used + A->used;
  if (pa >= FP_SIZE) {
     pa = FP_SIZE-1;
  }


  COMBA_START;
  CLEAR_CARRY;

  if (A == B) {
     fp_zero(&tmp);
     dst = &tmp;
  } else {
     fp_zero(B);
     dst = B;
  }

  for (ix = 0; ix < pa; ix++) {
      int      tx, ty, iy;
      fp_digit *tmpy, *tmpx;


      ty = MIN(A->used-1, ix);
      tx = ix - ty;


      tmpx = A->dp + tx;
      tmpy = A->dp + ty;


      iy = MIN(A->used-tx, ty+1);


      iy = MIN(iy, (ty-tx+1)>>1);


      CARRY_FORWARD;


      for (iz = 0; iz < iy; iz++) {
          SQRADD2(*tmpx++, *tmpy--);
      }


      if ((ix&1) == 0) {
          SQRADD(A->dp[ix>>1], A->dp[ix>>1]);
      }


      COMBA_STORE(dst->dp[ix]);
  }

  COMBA_FINI;


  dst->used = pa;
  fp_clamp (dst);
  if (dst != B) {
     fp_copy(dst, B);
  }
}
