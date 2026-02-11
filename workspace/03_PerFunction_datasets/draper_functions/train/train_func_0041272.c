insert_method_into_method_map (bool class_method, tree method)
{
  tree method_name = METHOD_SEL_NAME (method);
  tree existing_entry;
  objc_map_t map;

  if (class_method)
    map = class_method_map;
  else
    map = instance_method_map;


  existing_entry = objc_map_get (map, method_name);


  if (existing_entry == OBJC_MAP_NOT_FOUND)
    objc_map_put (map, method_name, method);
  else
    {
      tree new_entry;


      if (TREE_CODE (existing_entry) != TREE_VEC)
	{


	  if (comp_proto_with_proto (method, existing_entry, 1))
	    return;


	  new_entry = make_tree_vec (2);

	  TREE_VEC_ELT (new_entry, 0) = existing_entry;
	  TREE_VEC_ELT (new_entry, 1) = method;
	}
      else
	{


	  size_t i;


	  for (i = 0; i < (size_t) TREE_VEC_LENGTH (existing_entry); i++)
	    if (comp_proto_with_proto (method, TREE_VEC_ELT (existing_entry, i), 1))
	      return;


	  new_entry = make_tree_vec (TREE_VEC_LENGTH (existing_entry) + 1);


	  for (i = 0; i < (size_t) TREE_VEC_LENGTH (existing_entry); i++)
	    TREE_VEC_ELT (new_entry, i) = TREE_VEC_ELT (existing_entry, i);


	  TREE_VEC_ELT (new_entry, i) = method;
	}


      objc_map_put (map, method_name, new_entry);
    }
}
