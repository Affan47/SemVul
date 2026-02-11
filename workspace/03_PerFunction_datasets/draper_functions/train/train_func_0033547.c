mark_link_array(void *v,void *ve) {

  void **p,**pe;

  if (NULL_OR_ON_C_STACK(v))
    return;

  if (sLAlink_arrayA->s.s_dbind==Cnil)
    return;

  p=(void *)sLAlink_arrayA->s.s_dbind->v.v_self;
  pe=(void *)p+sLAlink_arrayA->s.s_dbind->v.v_fillp;

  if (is_marked(sLAlink_arrayA->s.s_dbind) && COLLECT_RELBLOCK_P
#ifdef SGC
      && (!sgc_enabled || SGC_RELBLOCK_P(sLAlink_arrayA->s.s_dbind->v.v_self))
#endif
      ) {
    fixnum j=rb_pointer1-rb_pointer;
    p=(void *)p+j;
    pe=(void *)pe+j;
  }

  for (;p<pe;p+=2)
    if (*p>=v && *p<ve) {
      massert(!LINK_ARRAY_MARKED(p));
#ifdef SGC
      if(!sgc_enabled || IS_WRITABLE(page(p)))
#endif
	MARK_LINK_ARRAY(p);
    }

}
