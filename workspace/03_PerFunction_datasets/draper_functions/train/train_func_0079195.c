_fmpz_poly_scalar_mul_si(fmpz_poly_t output, const fmpz_poly_t poly, const long x)
{
     if (x == 0)
     {
        unsigned long size = output->limbs + 1;
        for (long i = 0; i < poly->length; i++)
        {
           output->coeffs[i*size] = 0L;
        }
        output->length = 0;
        return;
     }

     fmpz_t coeffs1 = poly->coeffs;
     fmpz_t coeffs_out = output->coeffs;
     unsigned long size1 = poly->limbs+1;
     unsigned long size_out = output->limbs+1;
     mp_limb_t mslimb;

     for (long i = 0; i < poly->length; i++)
     {
        if (x < 0)
        {
           if ((coeffs_out[i*size_out] = -coeffs1[i*size1]))
           {
              mslimb = mpn_mul_1(coeffs_out+i*size_out+1, coeffs1+i*size1+1, ABS(coeffs1[i*size1]), -x);
              if (mslimb)
              {
                 coeffs_out[i*size_out+ABS(coeffs1[i*size1])+1] = mslimb;
                 if ((long) coeffs_out[i*size_out] > 0) coeffs_out[i*size_out]++;
                 else coeffs_out[i*size_out]--;
              }
           }
        } else
        {
           if ((coeffs_out[i*size_out] = coeffs1[i*size1]))
           {
              mslimb = mpn_mul_1(coeffs_out+i*size_out+1, coeffs1+i*size1+1, ABS(coeffs1[i*size1]), x);
              if (mslimb)
              {
                 coeffs_out[i*size_out+ABS(coeffs1[i*size1])+1] = mslimb;
                 if ((long) coeffs_out[i*size_out] > 0) coeffs_out[i*size_out]++;
                 else coeffs_out[i*size_out]--;
              }
           }
        }
     }
     output->length = poly->length;
}
