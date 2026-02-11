ecm_sqrredc_basecase_n (mp_ptr rp, mp_srcptr s1p,
                        mp_srcptr np, mp_size_t nn, mp_ptr invm, mp_ptr tmp)
{
  mp_limb_t cy;
  mp_size_t j;

  if (nn <= MULREDC_ASSEMBLY_MAX)
    {
      switch (tune_sqrredc_table[nn])
        {
        case MPMOD_MULREDC:
#ifdef USE_ASM_REDC
          mulredc (rp, s1p, s1p, np, nn, invm[0]);
          break;
#endif
        case MPMOD_MUL_REDC1:
#ifdef HAVE___GMPN_REDC_1
          mpn_sqr (tmp, s1p, nn);
          REDC1(rp, tmp, np, nn, invm[0]);
          break;
#endif
        case MPMOD_MUL_REDC2:
#ifdef HAVE___GMPN_REDC_2
          mpn_sqr (tmp, s1p, nn);
          REDC2(rp, tmp, np, nn, invm);
          break;
#endif
        case MPMOD_MUL_REDCN:
#ifdef HAVE___GMPN_REDC_N
          mpn_sqr (tmp, s1p, nn);
          __gmpn_redc_n (rp, tmp, np, nn, invm);
          break;
#endif
        case MPMOD_MUL_REDC_C:
          mpn_sqr (tmp, s1p, nn);
          for (j = 0; j < nn; j++, tmp++)
            tmp[0] = mpn_addmul_1 (tmp, np, nn, tmp[0] * invm[0]);
          cy = mpn_add_n (rp, tmp - nn, tmp, nn);
          if (cy != 0)
            mpn_sub_n (rp, rp, np, nn);
          break;
        default:
          {
            outputf (OUTPUT_ERROR, "Invalid sqrredc mode: %d\n",
                     tune_sqrredc_table[nn]);
            exit (EXIT_FAILURE);
          }
        }
    }
  else
    {
      mpn_sqr (tmp, s1p, nn);
      ecm_redc_n (rp, tmp, 2 * nn, np, invm, nn);
    }
}
