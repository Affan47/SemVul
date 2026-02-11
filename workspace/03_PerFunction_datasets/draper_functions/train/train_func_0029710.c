vector_get_eval_abc_count(
  vector* vec
) { PROFILE(VECTOR_GET_EVAL_ABC_COUNT);

  int          count = 0;
  unsigned int i, j;

  switch( vec->suppl.part.data_type ) {
    case VDATA_UL :
      for( i=0; i<UL_SIZE( vec->width ); i++ ) {
        ulong value_a = vec->value.ul[i][VTYPE_INDEX_EXP_EVAL_A];
        ulong value_b = vec->value.ul[i][VTYPE_INDEX_EXP_EVAL_B];
        ulong value_c = vec->value.ul[i][VTYPE_INDEX_EXP_EVAL_C];
        for( j=0; j<UL_BITS; j++ ) {
          count += (value_a >> j) & 0x1;
          count += (value_b >> j) & 0x1;
          count += (value_c >> j) & 0x1;
        }
      }
      break;
    case VDATA_R64 :
      break;
    default :  assert( 0 );  break;
  }

  PROFILE_END;

  return( count );

}
