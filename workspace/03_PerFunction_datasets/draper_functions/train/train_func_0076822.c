toElem (IRState *)
{
  Type *tb = type->toBasetype();

  dinteger_t dim = len + (tb->ty == Tpointer);

  tree value = build_string (dim * sz, (char *) string);


  TREE_TYPE (value) = d_array_type (tb->nextOf(), len);
  TREE_CONSTANT (value) = 1;
  TREE_READONLY (value) = 1;

  switch (tb->ty)
    {
    case Tarray:
      value = d_array_value (type->toCtype(), size_int (len), build_address (value));
      break;

    case Tpointer:
      value = build_address (value);
      break;

    case Tsarray:
      TREE_TYPE (value) = type->toCtype();
      break;

    default:
      error ("Invalid type for string constant: %s", type->toChars());
      return error_mark_node;
    }

  return value;
}
