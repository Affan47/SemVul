add_type_attribute (dw_die_ref object_die, tree type, int decl_const,
		    int decl_volatile, dw_die_ref context_die)
{
  enum tree_code code  = TREE_CODE (type);
  dw_die_ref type_die  = NULL;


  if ((code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE)
      && TREE_TYPE (type) != 0 && TYPE_NAME (type) == 0)
    type = TREE_TYPE (type), code = TREE_CODE (type);

  if (code == ERROR_MARK


      || code == VOID_TYPE)
    return;

  type_die = modified_type_die (type,
				decl_const || TYPE_READONLY (type),
				decl_volatile || TYPE_VOLATILE (type),
				context_die);

  if (type_die != NULL)
    add_AT_die_ref (object_die, DW_AT_type, type_die);
}
