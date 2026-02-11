compute_record_mode (tree type)
{
  tree field;
  enum machine_mode mode = VOIDmode;


  SET_TYPE_MODE (type, BLKmode);

  if (! host_integerp (TYPE_SIZE (type), 1))
    return;


  for (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      if (TREE_CODE (field) != FIELD_DECL)
	continue;

      if (TREE_CODE (TREE_TYPE (field)) == ERROR_MARK
	  || (TYPE_MODE (TREE_TYPE (field)) == BLKmode
	      && ! TYPE_NO_FORCE_BLK (TREE_TYPE (field))
	      && !(TYPE_SIZE (TREE_TYPE (field)) != 0
		   && integer_zerop (TYPE_SIZE (TREE_TYPE (field)))))
	  || ! host_integerp (bit_position (field), 1)
	  || DECL_SIZE (field) == 0
	  || ! host_integerp (DECL_SIZE (field), 1))
	return;


      if (simple_cst_equal (TYPE_SIZE (type), DECL_SIZE (field)))
	mode = DECL_MODE (field);

#ifdef MEMBER_TYPE_FORCES_BLK


      if (MEMBER_TYPE_FORCES_BLK (field, mode))
	return;
#endif
    }


  if (TREE_CODE (type) == RECORD_TYPE && mode != VOIDmode
      && host_integerp (TYPE_SIZE (type), 1)
      && GET_MODE_BITSIZE (mode) == TREE_INT_CST_LOW (TYPE_SIZE (type)))
    SET_TYPE_MODE (type, mode);
  else
    SET_TYPE_MODE (type, mode_for_size_tree (TYPE_SIZE (type), MODE_INT, 1));


  if (TYPE_MODE (type) != BLKmode
      && STRICT_ALIGNMENT
      && ! (TYPE_ALIGN (type) >= BIGGEST_ALIGNMENT
	    || TYPE_ALIGN (type) >= GET_MODE_ALIGNMENT (TYPE_MODE (type))))
    {


      TYPE_NO_FORCE_BLK (type) = 1;
      SET_TYPE_MODE (type, BLKmode);
    }
}
