get_name_arrayptr(int name_id,  REAL *newstack, struct locallist_t *localbase)
{
  if ( (name_id & GTYPEMASK) == ATTRIBNAME )
  { struct extra *ex = EXTRAS(name_eltype(name_id)) + (name_id & GLOBMASK);
    return &(ex->array_spec);
  }
  else
  { struct global *g;
    g = globals(name_id);

    if ( newstack && ((g->flags & (GLOB_LOCALVAR|FIXED_SIZE_ARRAY))==GLOB_LOCALVAR) )
       return *(struct array **)(newstack+g->value.offset);
    else
       return g->attr.arrayptr;
  }

  return NULL;
}
