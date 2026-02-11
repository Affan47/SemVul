finish_vector_type (t)
     tree t;
{
  layout_type (t);

  {
    tree index = build_int_2 (TYPE_VECTOR_SUBPARTS (t) - 1, 0);
    tree array = build_array_type (TREE_TYPE (t),
				   build_index_type (index));
    tree rt = make_node (RECORD_TYPE);

    TYPE_FIELDS (rt) = build_decl (FIELD_DECL, get_identifier ("f"), array);
    DECL_CONTEXT (TYPE_FIELDS (rt)) = rt;
    layout_type (rt);
    TYPE_DEBUG_REPRESENTATION_TYPE (t) = rt;


    TYPE_UID (rt) = TYPE_UID (t);
  }
}
