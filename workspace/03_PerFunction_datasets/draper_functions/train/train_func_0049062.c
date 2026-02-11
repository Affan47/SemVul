get_name_name(int name_id, struct locallist_t *localbase)
{
  if ( (name_id & GTYPEMASK) == ATTRIBNAME )
  { struct extra *ex = EXTRAS(name_eltype(name_id)) + (name_id & GLOBMASK);
    return ex->name;
  }
  else
  { struct global *g;
    g = globals(name_id);
    return g->name;
  }

  return NULL;
}
