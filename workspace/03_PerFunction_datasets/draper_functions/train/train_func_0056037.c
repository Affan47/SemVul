record_locally_defined_typedef (tree decl)
{
  struct c_language_function *l;

  if (!warn_unused_local_typedefs
      || cfun == NULL


      || !is_typedef_decl (decl)
      || !decl_function_context (decl))
    return;

  l = (struct c_language_function *) cfun->language;
  VEC_safe_push (tree, gc, l->local_typedefs, decl);
}
