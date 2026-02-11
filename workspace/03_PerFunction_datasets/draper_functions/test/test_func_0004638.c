check_ok_for_atomic (tree object, Entity_Id gnat_entity, bool comp_p)
{
  Node_Id gnat_error_point = gnat_entity;
  Node_Id gnat_node;
  enum machine_mode mode;
  unsigned int align;
  tree size;


  if (TYPE_P (object))
    {


      if (!Comes_From_Source (gnat_entity))
	return;

      mode = TYPE_MODE (object);
      align = TYPE_ALIGN (object);
      size = TYPE_SIZE (object);
    }
  else if (DECL_BY_REF_P (object))
    {
      mode = TYPE_MODE (TREE_TYPE (TREE_TYPE (object)));
      align = TYPE_ALIGN (TREE_TYPE (TREE_TYPE (object)));
      size = TYPE_SIZE (TREE_TYPE (TREE_TYPE (object)));
    }
  else
    {
      mode = DECL_MODE (object);
      align = DECL_ALIGN (object);
      size = DECL_SIZE (object);
    }


  if (GET_MODE_CLASS (mode) == MODE_FLOAT
      || ((GET_MODE_CLASS (mode) == MODE_INT
	   || GET_MODE_CLASS (mode) == MODE_PARTIAL_INT)
	  && GET_MODE_BITSIZE (mode) <= BITS_PER_WORD))
    return;


  if (size && TREE_CODE (size) == INTEGER_CST
      && compare_tree_int (size, align) == 0
      && align <= BITS_PER_WORD)
    return;

  for (gnat_node = First_Rep_Item (gnat_entity); Present (gnat_node);
       gnat_node = Next_Rep_Item (gnat_node))
    {
      if (!comp_p && Nkind (gnat_node) == N_Pragma
	  && (Get_Pragma_Id (Chars (Pragma_Identifier (gnat_node)))
              == Pragma_Atomic))
	gnat_error_point = First (Pragma_Argument_Associations (gnat_node));
      else if (comp_p && Nkind (gnat_node) == N_Pragma
	       && (Get_Pragma_Id (Chars (Pragma_Identifier (gnat_node)))
		   == Pragma_Atomic_Components))
	gnat_error_point = First (Pragma_Argument_Associations (gnat_node));
    }

  if (comp_p)
    post_error_ne ("atomic access to component of & cannot be guaranteed",
		   gnat_error_point, gnat_entity);
  else
    post_error_ne ("atomic access to & cannot be guaranteed",
		   gnat_error_point, gnat_entity);
}
