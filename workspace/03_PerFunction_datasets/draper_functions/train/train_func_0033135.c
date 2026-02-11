a68_string_size (NODE_T * p, A68_REF row)
{
  (void) p;
  if (INITIALISED (&row)) {
    A68_ARRAY *arr;
    A68_TUPLE *tup;
    GET_DESCRIPTOR (arr, tup, &row);
    return (ROW_SIZE (tup));
  } else {
    return (0);
  }
}
