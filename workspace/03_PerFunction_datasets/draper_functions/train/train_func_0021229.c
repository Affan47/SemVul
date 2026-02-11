gf_w32_bytwo_init(gf_t *gf)
{
  gf_internal_t *h;
  uint64_t ip, m1, m2;
  struct gf_w32_bytwo_data *btd;

  h = (gf_internal_t *) gf->scratch;
  btd = (struct gf_w32_bytwo_data *) (h->private);
  ip = h->prim_poly & 0xffffffff;
  m1 = 0xfffffffe;
  m2 = 0x80000000;
  btd->prim_poly = 0;
  btd->mask1 = 0;
  btd->mask2 = 0;

  while (ip != 0) {
    btd->prim_poly |= ip;
    btd->mask1 |= m1;
    btd->mask2 |= m2;
    ip <<= GF_FIELD_WIDTH;
    m1 <<= GF_FIELD_WIDTH;
    m2 <<= GF_FIELD_WIDTH;
  }

  if (h->mult_type == GF_MULT_BYTWO_p) {
    gf->multiply.w32 = gf_w32_bytwo_p_multiply;
    #ifdef INTEL_SSE2
      if (h->region_type & GF_REGION_NOSSE)
        gf->multiply_region.w32 = gf_w32_bytwo_p_nosse_multiply_region;
      else
        gf->multiply_region.w32 = gf_w32_bytwo_p_sse_multiply_region;
    #else
      gf->multiply_region.w32 = gf_w32_bytwo_p_nosse_multiply_region;
      if(h->region_type & GF_REGION_SSE)
        return 0;
    #endif
  } else {
    gf->multiply.w32 = gf_w32_bytwo_b_multiply;
    #ifdef INTEL_SSE2
      if (h->region_type & GF_REGION_NOSSE)
        gf->multiply_region.w32 = gf_w32_bytwo_b_nosse_multiply_region;
      else
        gf->multiply_region.w32 = gf_w32_bytwo_b_sse_multiply_region;
    #else
      gf->multiply_region.w32 = gf_w32_bytwo_b_nosse_multiply_region;
      if(h->region_type & GF_REGION_SSE)
        return 0;
    #endif
  }

  gf->inverse.w32 = gf_w32_euclid;
  return 1;
}
