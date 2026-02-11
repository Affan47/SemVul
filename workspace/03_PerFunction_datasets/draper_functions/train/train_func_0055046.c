gf_w64_bytwo_init(gf_t *gf)
{
  gf_internal_t *h;

  h = (gf_internal_t *) gf->scratch;

  if (h->mult_type == GF_MULT_BYTWO_p) {
    gf->multiply.w64 = gf_w64_bytwo_p_multiply;
    #ifdef INTEL_SSE2
      if (h->region_type & GF_REGION_NOSSE)
        gf->multiply_region.w64 = gf_w64_bytwo_p_nosse_multiply_region;
      else
        gf->multiply_region.w64 = gf_w64_bytwo_p_sse_multiply_region;
    #else
      gf->multiply_region.w64 = gf_w64_bytwo_p_nosse_multiply_region;
      if(h->region_type & GF_REGION_SSE)
        return 0;
    #endif
  } else {
    gf->multiply.w64 = gf_w64_bytwo_b_multiply;
    #ifdef INTEL_SSE2
      if (h->region_type & GF_REGION_NOSSE)
        gf->multiply_region.w64 = gf_w64_bytwo_b_nosse_multiply_region;
      else
        gf->multiply_region.w64 = gf_w64_bytwo_b_sse_multiply_region;
    #else
      gf->multiply_region.w64 = gf_w64_bytwo_b_nosse_multiply_region;
      if(h->region_type & GF_REGION_SSE)
        return 0;
    #endif
  }
  gf->inverse.w64 = gf_w64_euclid;
  return 1;
}
