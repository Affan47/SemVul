mark_named_operators (cpp_reader *pfile)
{
  const struct builtin *b;

  for (b = operator_array;
       b < (operator_array + ARRAY_SIZE (operator_array));
       b++)
    {
      cpp_hashnode *hp = cpp_lookup (pfile, b->name, b->len);
      hp->flags |= NODE_OPERATOR;
      hp->is_directive = 0;
      hp->directive_index = b->value;
    }
}
