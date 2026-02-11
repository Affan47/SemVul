ainfo_dup(
	  struct attrinfo	*a,
	  struct attrinfo	*b
)
{

  if (b->ai_indexmask == 0 || b->ai_indexmask == INDEX_OFFLINE) {
    a->ai_indexmask = INDEX_OFFLINE;
    charray_free ( a->ai_index_rules );
    a->ai_index_rules = NULL;
  }
  a->ai_indexmask |= b->ai_indexmask;
  if ( b->ai_indexmask & INDEX_RULES ) {
    charray_merge( &a->ai_index_rules, b->ai_index_rules, 1 );
  }

  attrinfo_delete_idlistinfo(&a->ai_idlistinfo);
  a->ai_idlistinfo = b->ai_idlistinfo;
  b->ai_idlistinfo = NULL;

  return( 1 );
}
