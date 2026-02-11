finish_label_decl (tree name)
{
  if (!at_function_scope_p ())
    {
      error ("__label__ declarations are only allowed in function scopes");
      return;
    }

  add_decl_expr (declare_local_label (name));
}
