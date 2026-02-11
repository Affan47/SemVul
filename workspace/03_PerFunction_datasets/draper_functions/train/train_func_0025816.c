mul_mod (mpi_ptr_t xp, mpi_size_t *xsize_p,
         mpi_ptr_t rp, mpi_size_t rsize,
         mpi_ptr_t sp, mpi_size_t ssize,
         mpi_ptr_t mp, mpi_size_t msize,
         struct karatsuba_ctx *karactx_p)
{
  if( ssize < KARATSUBA_THRESHOLD )
    _gcry_mpih_mul ( xp, rp, rsize, sp, ssize );
  else
    _gcry_mpih_mul_karatsuba_case (xp, rp, rsize, sp, ssize, karactx_p);

   if (rsize + ssize > msize)
    {
      _gcry_mpih_divrem (xp + msize, 0, xp, rsize + ssize, mp, msize);
      *xsize_p = msize;
    }
   else
     *xsize_p = rsize + ssize;
}
