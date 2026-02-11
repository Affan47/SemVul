struct_union_dealloc(
  struct_union* su
) { PROFILE(STRUCT_UNION_DEALLOC);

  su_member* curr_mem;
  su_member* tmp_mem;

  if( su != NULL ) {


    curr_mem = su->mem_head;
    while( curr_mem != NULL ) {
      tmp_mem = curr_mem;
      curr_mem = curr_mem->next;
      struct_union_member_dealloc( tmp_mem );
    }


    free_safe( su->name, (strlen( su->name ) + 1) );


    free_safe( su, sizeof( su_member ) );

  }

  PROFILE_END;

}
