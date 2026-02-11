reconvert_bodies_to_quantities()
{ int type;
  int k;
  struct method_instance *mi;
  struct element *e_ptr;
  body_id b_id;
  element_id id;

  for ( type = VERTEX ; type <= FACET ; type++ )
  { int meth_offset = get_meth_offset(type);
    int *methlist;
    FOR_ALL_ELEMENTS(type,id)
    { e_ptr = elptr(id);
      methlist = (int*)((char*)e_ptr+meth_offset);
      for ( k = 0 ; k < (int)e_ptr->method_count ; k++ )
      {
        mi = METH_INSTANCE(abs(methlist[k]));
        if ( mi->flags & BODY_INSTANCE )
        { methlist[k] = methlist[--(e_ptr->method_count)];
          k--;
        }
      }
    }
  }
  FOR_ALL_BODIES(b_id)
     convert_new_body_to_quantity(b_id);
  convert_bodies_to_quantities();
}
