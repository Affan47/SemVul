vector_op_inc(
  vector* tgt,
  vecblk* tvb
) { PROFILE(VECTOR_OP_INC);

  switch( tgt->suppl.part.data_type ) {
    case VDATA_UL :
      {
        vector* tmp1 = &(tvb->vec[tvb->index++]);
        vector* tmp2 = &(tvb->vec[tvb->index++]);
        vector_copy( tgt, tmp1 );
        tmp2->value.ul[0][VTYPE_INDEX_VAL_VALL] = 1;
        (void)vector_op_add( tgt, tmp1, tmp2 );
      }
      break;
    case VDATA_R64 :
      tgt->value.r64->val += 1.0;
      break;
    case VDATA_R32 :
      tgt->value.r32->val += 1.0;
      break;
    default :  assert( 0 );  break;
  }

  PROFILE_END;

  return( TRUE );

}
