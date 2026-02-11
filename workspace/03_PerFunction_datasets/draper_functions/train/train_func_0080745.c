push_binding (tree id, tree decl, cp_binding_level* level)
{
  cxx_binding *binding;

  if (level != class_binding_level)
    {
      binding = cxx_binding_make (decl, NULL_TREE);
      binding->scope = level;
    }
  else
    binding = new_class_binding (id, decl, NULL_TREE, level);


  binding->previous = IDENTIFIER_BINDING (id);
  INHERITED_VALUE_BINDING_P (binding) = 0;
  LOCAL_BINDING_P (binding) = (level != class_binding_level);


  IDENTIFIER_BINDING (id) = binding;
}
