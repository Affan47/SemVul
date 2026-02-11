vector_ceq_ulong(
  const vector* left,
  const vector* right
) { PROFILE(VECTOR_CEQ_ULONG);

  unsigned int lsize       = UL_SIZE(left->width);
  unsigned int rsize       = UL_SIZE(right->width);
  int          i           = ((lsize < rsize) ? rsize : lsize);
  unsigned int lmsb        = (left->width - 1);
  unsigned int rmsb        = (right->width - 1);
  bool         lmsb_is_one = (((left->value.ul[UL_DIV(lmsb)][VTYPE_INDEX_VAL_VALL]  >> UL_MOD(lmsb)) & 1) == 1);
  bool         rmsb_is_one = (((right->value.ul[UL_DIV(rmsb)][VTYPE_INDEX_VAL_VALL] >> UL_MOD(rmsb)) & 1) == 1);
  ulong        lvall;
  ulong        lvalh;
  ulong        rvall;
  ulong        rvalh;

  do {
    i--;
    vector_copy_val_and_sign_extend_ulong( left,  i, lmsb_is_one, &lvall, &lvalh );
    vector_copy_val_and_sign_extend_ulong( right, i, rmsb_is_one, &rvall, &rvalh );
  } while( (i > 0) && (lvall == rvall) && (lvalh == rvalh) );

  PROFILE_END;

  return( (lvall == rvall) && (lvalh == rvalh) );

}
