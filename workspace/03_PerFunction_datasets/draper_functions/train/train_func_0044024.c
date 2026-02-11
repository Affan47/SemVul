array_and_function_declarators_opt (type_p ty)
{
  if (token () == ARRAY)
    {
      const char *array = advance ();
      return create_array (array_and_function_declarators_opt (ty), array);
    }
  else if (token () == '(')
    {

      consume_balanced ('(', ')');
      array_and_function_declarators_opt (ty);
      return create_scalar_type ("function type");
    }
  else
    return ty;
}
