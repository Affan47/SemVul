resolution_filter (pIIR_Declaration d, void *closure)
{
  resolution_filter_closure *rfc = (resolution_filter_closure *)closure;

  if (!d->is(IR_FUNCTION_DECLARATION))
    return -1;

  pIIR_FunctionDeclaration f = pIIR_FunctionDeclaration(d);
  if (!f->pure)
    return -1;
  if (vaul_get_base (f->return_type) != rfc->base)
    return -1;
  if (f->interface_declarations == NULL
      || f->interface_declarations->rest != NULL)
    return -1;

  pIIR_InterfaceDeclaration p = f->interface_declarations->first;
  if (!p->is(IR_CONSTANT_INTERFACE_DECLARATION) || p->mode != IR_IN_MODE)
    return -1;
  if (!p->subtype->is(IR_ARRAY_TYPE))
    return -1;

  pIIR_ArrayType pt = pIIR_ArrayType (p->subtype);
  if (pt->index_types == NULL || pt->index_types->rest != NULL)
    return -1;
  if (vaul_get_base (pt->element_type) != rfc->base)
    return -1;

  return 0;
}
