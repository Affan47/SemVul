build_dummy_unc_pointer_types (Entity_Id gnat_desig_type, tree gnu_desig_type)
{
  tree gnu_template_type, gnu_ptr_template, gnu_array_type, gnu_ptr_array;
  tree gnu_fat_type, fields, gnu_object_type;

  gnu_template_type = make_node (RECORD_TYPE);
  TYPE_NAME (gnu_template_type) = create_concat_name (gnat_desig_type, "XUB");
  TYPE_DUMMY_P (gnu_template_type) = 1;
  gnu_ptr_template = build_pointer_type (gnu_template_type);

  gnu_array_type = make_node (ENUMERAL_TYPE);
  TYPE_NAME (gnu_array_type) = create_concat_name (gnat_desig_type, "XUA");
  TYPE_DUMMY_P (gnu_array_type) = 1;
  gnu_ptr_array = build_pointer_type (gnu_array_type);

  gnu_fat_type = make_node (RECORD_TYPE);


  TYPE_NAME (gnu_fat_type)
    = create_type_stub_decl (create_concat_name (gnat_desig_type, "XUP"),
			     gnu_fat_type);
  fields = create_field_decl (get_identifier ("P_ARRAY"), gnu_ptr_array,
			      gnu_fat_type, NULL_TREE, NULL_TREE, 0, 0);
  DECL_CHAIN (fields)
    = create_field_decl (get_identifier ("P_BOUNDS"), gnu_ptr_template,
			 gnu_fat_type, NULL_TREE, NULL_TREE, 0, 0);
  finish_fat_pointer_type (gnu_fat_type, fields);
  SET_TYPE_UNCONSTRAINED_ARRAY (gnu_fat_type, gnu_desig_type);

  TYPE_DECL_SUPPRESS_DEBUG (TYPE_STUB_DECL (gnu_fat_type)) = 1;

  gnu_object_type = make_node (RECORD_TYPE);
  TYPE_NAME (gnu_object_type) = create_concat_name (gnat_desig_type, "XUT");
  TYPE_DUMMY_P (gnu_object_type) = 1;

  TYPE_POINTER_TO (gnu_desig_type) = gnu_fat_type;
  TYPE_OBJECT_RECORD_TYPE (gnu_desig_type) = gnu_object_type;
}
