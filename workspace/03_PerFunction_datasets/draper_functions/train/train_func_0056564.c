write_stub_methods(type_t *iface, int skip)
{
  const statement_t *stmt;
  int i = 0;

  if (type_iface_get_inherit(iface))
    i = write_stub_methods(type_iface_get_inherit(iface), need_delegation(iface));
  else
    return i;

  STATEMENTS_FOR_EACH_FUNC(stmt, type_iface_get_stmts(iface)) {
    const var_t *func = stmt->u.var;
    if (!is_callas(func->attrs)) {
      int missing = 0;
      const char * fname = get_name(func);
      if(is_local(func->attrs)) {
        const statement_t * callas_source = get_callas_source(iface, func);
        if(!callas_source)
          missing = 1;
        else
          fname = get_name(callas_source->u.var);
      }
      if (i) fprintf(proxy,",\n");
      if (skip || missing) print_proxy("STUB_FORWARDING_FUNCTION");
      else if (is_interpreted_func( iface, func ))
          print_proxy( "(PRPC_STUB_FUNCTION)%s", get_stub_mode() == MODE_Oif ? "NdrStubCall2" : "NdrStubCall" );
      else print_proxy( "%s_%s_Stub", iface->name, fname);
      i++;
    }
  }
  return i;
}
