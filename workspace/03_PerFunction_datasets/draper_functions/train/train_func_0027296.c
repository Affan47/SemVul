lxt2_rd_limit_time_range(
  struct lxt2_rd_trace* lt,
  lxtint64_t            strt_time,
  lxtint64_t            end_time
) { PROFILE(LXT2_RD_LIMIT_TIME_RANGE);

  lxtint64_t tmp_time;
  int        blk = 0;

  if( lt ) {

    struct lxt2_rd_block* b     = lt->block_head;
    struct lxt2_rd_block* bprev = NULL;
    int                   state = 0;

    if( strt_time > end_time ) {
      tmp_time  = strt_time;
      strt_time = end_time;
      end_time  = tmp_time;
    }

    while( b ) {

      switch( state ) {
        case 0 :
          if( b->end >= strt_time ) {
            state = 1;
            if( (b->start > strt_time) && bprev ) {
              bprev->exclude_block = 0;
              blk++;
            }
          }
          break;
        case 1 :
          if( b->start > end_time ) {
            state = 2;
          }
          break;
        default:  break;
      }

      if( (state == 1) && !b->short_read_ignore ) {
        b->exclude_block = 0;
        blk++;
      } else {
        b->exclude_block = 1;
      }

      bprev = b;
      b = b->next;

    }

  }

  PROFILE_END;

  return( blk );

}
