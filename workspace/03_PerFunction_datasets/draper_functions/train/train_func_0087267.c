dbxout_range_type (tree type, tree low, tree high)
{
  stabstr_C ('r');
  if (TREE_TYPE (type))
    dbxout_type (TREE_TYPE (type), 0);
  else if (TREE_CODE (type) != INTEGER_TYPE)
    dbxout_type (type, 0);
  else
    {


      if (TYPE_SYMTAB_ADDRESS (type) != 0)
	dbxout_type_index (type);
      else
	dbxout_type_index (integer_type_node);
    }

  stabstr_C (';');
  if (low && host_integerp (low, 0))
    {
      if (print_int_cst_bounds_in_octal_p (type, low, high))
        stabstr_O (low);
      else
        stabstr_D (tree_low_cst (low, 0));
    }
  else
    stabstr_C ('0');

  stabstr_C (';');
  if (high && host_integerp (high, 0))
    {
      if (print_int_cst_bounds_in_octal_p (type, low, high))
        stabstr_O (high);
      else
        stabstr_D (tree_low_cst (high, 0));
      stabstr_C (';');
    }
  else
    stabstr_S ("-1;");
}
