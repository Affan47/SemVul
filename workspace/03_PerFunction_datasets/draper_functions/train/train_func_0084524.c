fini_copy_prop (void)
{
  unsigned i;


  for (i = 1; i < num_ssa_names; i++)
    {
      tree var = ssa_name (i);
      if (!var
	  || !copy_of[i].value
	  || copy_of[i].value == var)
	continue;


      if (copy_of[i].value != var
	  && TREE_CODE (copy_of[i].value) == SSA_NAME
	  && POINTER_TYPE_P (TREE_TYPE (var))
	  && SSA_NAME_PTR_INFO (var)
	  && !SSA_NAME_PTR_INFO (copy_of[i].value))
	duplicate_ssa_name_ptr_info (copy_of[i].value, SSA_NAME_PTR_INFO (var));
    }


  substitute_and_fold (get_value, NULL, !current_loops);

  free (copy_of);
}
