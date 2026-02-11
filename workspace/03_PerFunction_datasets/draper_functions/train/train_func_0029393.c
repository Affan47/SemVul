inform_declaration (tree decl)
{
  if (decl && (TREE_CODE (decl) != FUNCTION_DECL || !DECL_BUILT_IN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
}
