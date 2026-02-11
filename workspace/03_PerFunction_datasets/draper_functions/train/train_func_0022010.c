colour_row_elements (A68_REF * z, MOID_T * m)
{
  A68_ARRAY *arr;
  A68_TUPLE *tup;
  GET_DESCRIPTOR (arr, tup, z);
  if (get_row_size (tup, DIM (arr)) == 0) {

    BYTE_T *elem = ADDRESS (&ARRAY (arr));
    colour_object (&elem[0], SUB (m));
  } else {

    BYTE_T *elem = ADDRESS (&ARRAY (arr));
    BOOL_T done = A68_FALSE;
    initialise_internal_index (tup, DIM (arr));
    while (!done) {
      ADDR_T iindex = calculate_internal_index (tup, DIM (arr));
      ADDR_T addr = ROW_ELEMENT (arr, iindex);
      colour_object (&elem[addr], SUB (m));
      done = increment_internal_index (tup, DIM (arr));
    }
  }
}
