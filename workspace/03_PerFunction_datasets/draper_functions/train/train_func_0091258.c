staticp (tree arg)
{
  switch (TREE_CODE (arg))
    {
    case FUNCTION_DECL:


      return ((decl_function_context (arg) == 0 || DECL_NO_STATIC_CHAIN (arg))
	      && ! DECL_NON_ADDR_CONST_P (arg));

    case VAR_DECL:
      return ((TREE_STATIC (arg) || DECL_EXTERNAL (arg))
	      && ! DECL_THREAD_LOCAL (arg)
	      && ! DECL_NON_ADDR_CONST_P (arg));

    case CONSTRUCTOR:
      return TREE_STATIC (arg);

    case LABEL_DECL:
    case STRING_CST:
      return 1;


    case COMPONENT_REF:
      return (! DECL_BIT_FIELD (TREE_OPERAND (arg, 1))
	      && staticp (TREE_OPERAND (arg, 0)));

    case BIT_FIELD_REF:
      return 0;

#if 0


    case INDIRECT_REF:
      return TREE_CONSTANT (TREE_OPERAND (arg, 0));
#endif

    case ARRAY_REF:
    case ARRAY_RANGE_REF:
      if (TREE_CODE (TYPE_SIZE (TREE_TYPE (arg))) == INTEGER_CST
	  && TREE_CODE (TREE_OPERAND (arg, 1)) == INTEGER_CST)
	return staticp (TREE_OPERAND (arg, 0));

    default:
      if ((unsigned int) TREE_CODE (arg)
	  >= (unsigned int) LAST_AND_UNUSED_TREE_CODE)
	return (*lang_hooks.staticp) (arg);
      else
	return 0;
    }
}
