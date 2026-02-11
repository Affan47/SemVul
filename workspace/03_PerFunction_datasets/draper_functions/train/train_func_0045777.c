struct_union_create(
               const char* name,
   sig_range*  range,
               int         type,
               bool        packed,
               bool        is_signed,
               func_unit*  funit
) { PROFILE(STRUCT_UNION_CREATE);

  struct_union* su;


  su = (struct_union*)malloc_safe( sizeof( struct_union ) );


  su->name      = strdup_safe( name );
  su->type      = type;
  su->packed    = packed;
  su->is_signed = is_signed;
  su->mem_head  = NULL;
  su->mem_tail  = NULL;
  su->next      = NULL;


  if( funit->su_head == NULL ) {
    funit->su_head = funit->su_tail = su;
  } else {
    funit->su_tail->next = su;
    funit->su_tail       = su;
  }

  PROFILE_END;

  return( su );

}
