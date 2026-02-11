finalize_type_size (type)
     tree type;
{


  if (TYPE_MODE (type) != BLKmode && TYPE_MODE (type) != VOIDmode
      && (STRICT_ALIGNMENT
	  || (TREE_CODE (type) != RECORD_TYPE && TREE_CODE (type) != UNION_TYPE
	      && TREE_CODE (type) != QUAL_UNION_TYPE
	      && TREE_CODE (type) != ARRAY_TYPE)))
    {
      TYPE_ALIGN (type) = GET_MODE_ALIGNMENT (TYPE_MODE (type));
      TYPE_USER_ALIGN (type) = 0;
    }


#ifdef ROUND_TYPE_ALIGN
  TYPE_ALIGN (type)
    = ROUND_TYPE_ALIGN (type, TYPE_ALIGN (type), BITS_PER_UNIT);
#endif


  if (TYPE_SIZE_UNIT (type) == 0 && TYPE_SIZE (type) != 0)


    TYPE_SIZE_UNIT (type)
      = convert (sizetype,
		 size_binop (FLOOR_DIV_EXPR, TYPE_SIZE (type),
			     bitsize_unit_node));

  if (TYPE_SIZE (type) != 0)
    {
#ifdef ROUND_TYPE_SIZE
      TYPE_SIZE (type)
	= ROUND_TYPE_SIZE (type, TYPE_SIZE (type), TYPE_ALIGN (type));
      TYPE_SIZE_UNIT (type)
	= ROUND_TYPE_SIZE_UNIT (type, TYPE_SIZE_UNIT (type),
				TYPE_ALIGN (type) / BITS_PER_UNIT);
#else
      TYPE_SIZE (type) = round_up (TYPE_SIZE (type), TYPE_ALIGN (type));
      TYPE_SIZE_UNIT (type)
	= round_up (TYPE_SIZE_UNIT (type), TYPE_ALIGN (type) / BITS_PER_UNIT);
#endif
    }


  if (TYPE_SIZE (type) != 0 && TREE_CODE (TYPE_SIZE (type)) != INTEGER_CST)
    TYPE_SIZE (type) = variable_size (TYPE_SIZE (type));
  if (TYPE_SIZE_UNIT (type) != 0
      && TREE_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
    TYPE_SIZE_UNIT (type) = variable_size (TYPE_SIZE_UNIT (type));


  if (TYPE_NEXT_VARIANT (type)
      || type != TYPE_MAIN_VARIANT (type))
    {
      tree variant;

      tree size = TYPE_SIZE (type);
      tree size_unit = TYPE_SIZE_UNIT (type);
      unsigned int align = TYPE_ALIGN (type);
      unsigned int user_align = TYPE_USER_ALIGN (type);
      enum machine_mode mode = TYPE_MODE (type);


      for (variant = TYPE_MAIN_VARIANT (type);
	   variant != 0;
	   variant = TYPE_NEXT_VARIANT (variant))
	{
	  TYPE_SIZE (variant) = size;
	  TYPE_SIZE_UNIT (variant) = size_unit;
	  TYPE_ALIGN (variant) = align;
	  TYPE_USER_ALIGN (variant) = user_align;
	  TYPE_MODE (variant) = mode;
	}
    }
}
