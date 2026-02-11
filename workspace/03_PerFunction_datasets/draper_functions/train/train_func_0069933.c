is_ctor_or_dtor (mangled, ctor_kind, dtor_kind)
     const char *mangled;
     enum gnu_v3_ctor_kinds *ctor_kind;
     enum gnu_v3_dtor_kinds *dtor_kind;
{
  struct d_info di;
  struct demangle_component *dc;
  int ret;

  *ctor_kind = (enum gnu_v3_ctor_kinds) 0;
  *dtor_kind = (enum gnu_v3_dtor_kinds) 0;

  cplus_demangle_init_info (mangled, DMGL_GNU_V3, strlen (mangled), &di);

  {
#ifdef CP_DYNAMIC_ARRAYS
    __extension__ struct demangle_component comps[di.num_comps];
    __extension__ struct demangle_component *subs[di.num_subs];

    di.comps = &comps[0];
    di.subs = &subs[0];
#else
    di.comps = ((struct demangle_component *)
		malloc (di.num_comps * sizeof (struct demangle_component)));
    di.subs = ((struct demangle_component **)
	       malloc (di.num_subs * sizeof (struct demangle_component *)));
    if (di.comps == NULL || di.subs == NULL)
      {
	if (di.comps != NULL)
	  free (di.comps);
	if (di.subs != NULL)
	  free (di.subs);
	return 0;
      }
#endif

    dc = cplus_demangle_mangled_name (&di, 1);


    ret = 0;
    while (dc != NULL)
      {
	switch (dc->type)
	  {
	  default:
	    dc = NULL;
	    break;
	  case DEMANGLE_COMPONENT_TYPED_NAME:
	  case DEMANGLE_COMPONENT_TEMPLATE:
	  case DEMANGLE_COMPONENT_RESTRICT_THIS:
	  case DEMANGLE_COMPONENT_VOLATILE_THIS:
	  case DEMANGLE_COMPONENT_CONST_THIS:
	    dc = d_left (dc);
	    break;
	  case DEMANGLE_COMPONENT_QUAL_NAME:
	  case DEMANGLE_COMPONENT_LOCAL_NAME:
	    dc = d_right (dc);
	    break;
	  case DEMANGLE_COMPONENT_CTOR:
	    *ctor_kind = dc->u.s_ctor.kind;
	    ret = 1;
	    dc = NULL;
	    break;
	  case DEMANGLE_COMPONENT_DTOR:
	    *dtor_kind = dc->u.s_dtor.kind;
	    ret = 1;
	    dc = NULL;
	    break;
	  }
      }

#ifndef CP_DYNAMIC_ARRAYS
    free (di.subs);
    free (di.comps);
#endif
  }

  return ret;
}
