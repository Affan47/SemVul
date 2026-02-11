zn_array_mulmid_precomp1_clear (zn_array_mulmid_precomp1_t op)
{

   switch (op->algo)
   {
      case ZNP_MULMID_ALGO_KS:
         free (op->op1);
         break;

      case ZNP_MULMID_ALGO_FFT:
         zn_array_mulmid_fft_precomp1_clear (op->precomp_fft);
         free (op->precomp_fft);
         break;

      default: ZNP_ASSERT (0);
   }
}
