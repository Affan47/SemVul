atomic_sync_required_p (Node_Id gnat_node)
{
  const Node_Id gnat_parent = Parent (gnat_node);
  Node_Kind kind;
  unsigned char attr_id;


  kind = Nkind (gnat_node);
  if (kind == N_Type_Conversion || kind == N_Unchecked_Type_Conversion)
    {
      gnat_node = Expression (gnat_node);
      kind = Nkind (gnat_node);
    }

  switch (kind)
    {
    case N_Expanded_Name:
    case N_Explicit_Dereference:
    case N_Identifier:
    case N_Indexed_Component:
    case N_Selected_Component:
      if (!Atomic_Sync_Required (gnat_node))
	return false;
      break;

    default:
      return false;
    }


  kind = Nkind (gnat_parent);
  switch (kind)
    {
    case N_Attribute_Reference:
      attr_id = Get_Attribute_Id (Attribute_Name (gnat_parent));

      if (attr_id == Attr_Asm_Input || attr_id == Attr_Asm_Output)
	return false;
      break;

    case N_Object_Renaming_Declaration:

      return false;

    default:
      break;
    }

  return true;
}
