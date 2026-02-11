caml_ba_slice(value vb, value vind)
{
  CAMLparam2 (vb, vind);
  #define b ((struct caml_ba_array *) Caml_ba_array_val(vb))
  CAMLlocal1 (res);
  intnat index[CAML_BA_MAX_NUM_DIMS];
  int num_inds, i;
  intnat offset;
  intnat * sub_dims;
  char * sub_data;


  num_inds = Wosize_val(vind);
  if (num_inds >= b->num_dims)
    caml_invalid_argument("Bigarray.slice: too many indices");

  if ((b->flags & CAML_BA_LAYOUT_MASK) == CAML_BA_C_LAYOUT) {

    for (i = 0; i < num_inds; i++) index[i] = Long_val(Field(vind, i));
    for (; i < b->num_dims; i++) index[i] = 0;
    offset = caml_ba_offset(b, index);
    sub_dims = b->dim + num_inds;
  } else {

    for (i = 0; i < num_inds; i++)
      index[b->num_dims - num_inds + i] = Long_val(Field(vind, i));
    for (i = 0; i < b->num_dims - num_inds; i++) index[i] = 1;
    offset = caml_ba_offset(b, index);
    sub_dims = b->dim;
  }
  sub_data =
    (char *) b->data +
    offset * caml_ba_element_size[b->flags & CAML_BA_KIND_MASK];

  res = caml_ba_alloc(b->flags, b->num_dims - num_inds, sub_data, sub_dims);

  caml_ba_update_proxy(b, Caml_ba_array_val(res));

  CAMLreturn (res);

  #undef b
}
