intrin_return_compatible_p (intrin_binding_t * inb)
{
  tree ada_return_type = TREE_TYPE (inb->ada_fntype);
  tree btin_return_type = TREE_TYPE (inb->btin_fntype);


  if (VOID_TYPE_P (ada_return_type)
      && !VOID_TYPE_P (btin_return_type))
    return true;


  if (Is_Descendent_Of_Address (Etype (inb->gnat_entity)))
    ada_return_type = ptr_void_type_node;


  if (intrin_types_incompatible_p (btin_return_type, ada_return_type))
    {
      post_error ("?intrinsic binding type mismatch on return value!",
		  inb->gnat_entity);
      return false;
    }

  return true;
}
