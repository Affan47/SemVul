vector_part_select_pull(
  vector* tgt,
  vector* src,
  int     lsb,
  int     msb,
  bool    set_mem_rd
) { PROFILE(VECTOR_PART_SELECT_PULL);

  bool retval;

  switch( src->suppl.part.data_type ) {
    case VDATA_UL :
      {
        ulong valh[UL_DIV(MAX_BIT_WIDTH)];
        ulong vall[UL_DIV(MAX_BIT_WIDTH)];


        vector_rshift_ulong( src, vall, valh, lsb, msb, TRUE );


        if( set_mem_rd && (src->suppl.part.type == VTYPE_MEM) ) {
          if( UL_DIV(msb) == UL_DIV(lsb) ) {
            src->value.ul[UL_DIV(lsb)][VTYPE_INDEX_MEM_RD] |= UL_HMASK(msb) & UL_LMASK(lsb);
          } else {
            int i;
            src->value.ul[UL_DIV(lsb)][VTYPE_INDEX_MEM_RD] |= UL_LMASK(lsb);
            for( i=(UL_DIV(lsb) + 1); i<=UL_DIV(msb); i++ ) {
              src->value.ul[UL_DIV(msb)][VTYPE_INDEX_MEM_RD] = UL_SET;
            }
            src->value.ul[UL_DIV(msb)][VTYPE_INDEX_MEM_RD] |= UL_HMASK(msb);
          }
        }


        retval = vector_set_coverage_and_assign_ulong( tgt, vall, valh, 0, (tgt->width - 1) );
      }
      break;
    default :  assert( 0 );  break;
  }

  PROFILE_END;

  return( retval );

}
