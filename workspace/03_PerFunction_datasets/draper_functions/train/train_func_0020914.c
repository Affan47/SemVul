maybe_rewrite_mem_ref_base (tree *tp)
{
  tree sym;

  while (handled_component_p (*tp))
    tp = &TREE_OPERAND (*tp, 0);
  if (TREE_CODE (*tp) == MEM_REF
      && TREE_CODE (TREE_OPERAND (*tp, 0)) == ADDR_EXPR
      && (sym = TREE_OPERAND (TREE_OPERAND (*tp, 0), 0))
      && DECL_P (sym)
      && !TREE_ADDRESSABLE (sym)
      && symbol_marked_for_renaming (sym))
    {
      if (TREE_CODE (TREE_TYPE (sym)) == VECTOR_TYPE
	  && useless_type_conversion_p (TREE_TYPE (*tp),
					TREE_TYPE (TREE_TYPE (sym)))
	  && multiple_of_p (sizetype, TREE_OPERAND (*tp, 1),
			    TYPE_SIZE_UNIT (TREE_TYPE (*tp))))
	{
	  *tp = build3 (BIT_FIELD_REF, TREE_TYPE (*tp), sym,
			TYPE_SIZE (TREE_TYPE (*tp)),
			int_const_binop (MULT_EXPR,
					 bitsize_int (BITS_PER_UNIT),
					 TREE_OPERAND (*tp, 1)));
	}
      else if (TREE_CODE (TREE_TYPE (sym)) == COMPLEX_TYPE
	       && useless_type_conversion_p (TREE_TYPE (*tp),
					     TREE_TYPE (TREE_TYPE (sym))))
	{
	  *tp = build1 (integer_zerop (TREE_OPERAND (*tp, 1))
			? REALPART_EXPR : IMAGPART_EXPR,
			TREE_TYPE (*tp), sym);
	}
      else if (integer_zerop (TREE_OPERAND (*tp, 1)))
	{
	  if (!useless_type_conversion_p (TREE_TYPE (*tp),
					  TREE_TYPE (sym)))
	    *tp = build1 (VIEW_CONVERT_EXPR,
			  TREE_TYPE (*tp), sym);
	  else
	    *tp = sym;
	}
    }
}
