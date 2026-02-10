pop_arguments (tree method_type)
{
  function_args_iterator fnai;
  tree type;
  vec<tree, va_gc> *args = NULL;
  int arity;

  FOREACH_FUNCTION_ARGS (method_type, type, fnai)
    {

      if (type == void_type_node)
        break;

      vec_safe_push (args, type);
    }

  arity = vec_safe_length (args);

  while (arity--)
    {
      tree arg = pop_value ((*args)[arity]);


      if (TREE_CODE (type) == POINTER_TYPE)
	arg = build1 (NOP_EXPR, type, arg);
      else if (targetm.calls.promote_prototypes (type)
	       && TYPE_PRECISION (type) < TYPE_PRECISION (integer_type_node)
	       && INTEGRAL_TYPE_P (type))
	arg = convert (integer_type_node, arg);

      (*args)[arity] = arg;
    }

  return args;
}
