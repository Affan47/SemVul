build_v2_message_ref_translation_table (void)
{
  int count;
  msgref_entry *ref;

  if (!vec_safe_length (msgrefs))
    return;

  FOR_EACH_VEC_ELT (*msgrefs, count, ref)
    {
      vec<constructor_elt, va_gc> *initializer;
      tree expr, constructor;
      tree struct_type = TREE_TYPE (ref->refdecl);
      location_t loc = DECL_SOURCE_LOCATION (ref->refdecl);

      initializer = NULL;

      expr = build_unary_op (loc, ADDR_EXPR, ref->func, 0);
      expr = convert (objc_v2_imp_type, expr);
      CONSTRUCTOR_APPEND_ELT (initializer, NULL_TREE, expr);


      expr = build_selector (ref->selname);
      CONSTRUCTOR_APPEND_ELT (initializer, NULL_TREE, expr);
      constructor = objc_build_constructor (struct_type, initializer);
      finish_var_decl (ref->refdecl, constructor);
    }
}
