dbxout_type_method_1 (tree decl)
{
  char c1 = 'A', c2;

  if (TREE_CODE (TREE_TYPE (decl)) == FUNCTION_TYPE)
    c2 = '?';
  else
    {
      tree firstarg = TREE_VALUE (TYPE_ARG_TYPES (TREE_TYPE (decl)));


      if (TYPE_READONLY (TREE_TYPE (firstarg)))
	c1 += 1;
      if (TYPE_VOLATILE (TREE_TYPE (firstarg)))
	c1 += 2;

      if (DECL_VINDEX (decl))
	c2 = '*';
      else
	c2 = '.';
    }


  stabstr_C (':');
  stabstr_I (DECL_ASSEMBLER_NAME (decl));
  stabstr_C (';');
  stabstr_C (DECL_ACCESSIBILITY_CHAR (decl));
  stabstr_C (c1);
  stabstr_C (c2);

  if (DECL_VINDEX (decl) && host_integerp (DECL_VINDEX (decl), 0))
    {
      stabstr_D (tree_low_cst (DECL_VINDEX (decl), 0));
      stabstr_C (';');
      dbxout_type (DECL_CONTEXT (decl), 0);
      stabstr_C (';');
    }
}
