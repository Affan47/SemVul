finalize_record_size (record_layout_info rli)
{
  tree unpadded_size, unpadded_size_unit;


  rli->offset_align = BITS_PER_UNIT;
  normalize_rli (rli);


#ifdef ROUND_TYPE_ALIGN
  TYPE_ALIGN (rli->t) = ROUND_TYPE_ALIGN (rli->t, TYPE_ALIGN (rli->t),
					  rli->record_align);
#else
  TYPE_ALIGN (rli->t) = MAX (TYPE_ALIGN (rli->t), rli->record_align);
#endif


  unpadded_size = rli_size_so_far (rli);
  unpadded_size_unit = rli_size_unit_so_far (rli);
  if (! integer_zerop (rli->bitpos))
    unpadded_size_unit
      = size_binop (PLUS_EXPR, unpadded_size_unit, size_one_node);


  TYPE_SIZE (rli->t) = round_up (unpadded_size, TYPE_ALIGN (rli->t));
  TYPE_SIZE_UNIT (rli->t) = round_up (unpadded_size_unit,
				      TYPE_ALIGN (rli->t) / BITS_PER_UNIT);

  if (warn_padded && TREE_CONSTANT (unpadded_size)
      && simple_cst_equal (unpadded_size, TYPE_SIZE (rli->t)) == 0)
    warning ("padding struct size to alignment boundary");

  if (warn_packed && TREE_CODE (rli->t) == RECORD_TYPE
      && TYPE_PACKED (rli->t) && ! rli->packed_maybe_necessary
      && TREE_CONSTANT (unpadded_size))
    {
      tree unpacked_size;

#ifdef ROUND_TYPE_ALIGN
      rli->unpacked_align
	= ROUND_TYPE_ALIGN (rli->t, TYPE_ALIGN (rli->t), rli->unpacked_align);
#else
      rli->unpacked_align = MAX (TYPE_ALIGN (rli->t), rli->unpacked_align);
#endif

      unpacked_size = round_up (TYPE_SIZE (rli->t), rli->unpacked_align);
      if (simple_cst_equal (unpacked_size, TYPE_SIZE (rli->t)))
	{
	  TYPE_PACKED (rli->t) = 0;

	  if (TYPE_NAME (rli->t))
	    {
	      const char *name;

	      if (TREE_CODE (TYPE_NAME (rli->t)) == IDENTIFIER_NODE)
		name = IDENTIFIER_POINTER (TYPE_NAME (rli->t));
	      else
		name = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (rli->t)));

	      if (STRICT_ALIGNMENT)
		warning ("packed attribute causes inefficient alignment for `%s'", name);
	      else
		warning ("packed attribute is unnecessary for `%s'", name);
	    }
	  else
	    {
	      if (STRICT_ALIGNMENT)
		warning ("packed attribute causes inefficient alignment");
	      else
		warning ("packed attribute is unnecessary");
	    }
	}
    }
}
