race_get_stats(
            race_blk*     curr,
   unsigned int* race_total,
   unsigned int  type_total[][RACE_TYPE_NUM]
) { PROFILE(RACE_GET_STATS);

  int i;


  *race_total = 0;
  for( i=0; i<RACE_TYPE_NUM; i++ ) {
    (*type_total)[i] = 0;
  }


  while( curr != NULL ) {
    (*type_total)[curr->reason]++;
    (*race_total)++;
    curr = curr->next;
  }

  PROFILE_END;

}
