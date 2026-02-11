bgav_qt_user_atoms_append(qt_atom_header_t * h,
                               bgav_input_context_t * ctx,
                               qt_user_atoms_t * ret)
  {
  ret->atoms = realloc(ret->atoms,
                       (ret->num + 1) * sizeof(*ret->atoms));
  ret->atoms[ret->num] = malloc(h->size);
  BGAV_32BE_2_PTR(h->size, ret->atoms[ret->num]);
  BGAV_32BE_2_PTR(h->fourcc, ret->atoms[ret->num]+4);

  if(bgav_input_read_data(ctx, ret->atoms[ret->num]+8,
                          h->size - 8) < h->size - 8)
    return 0;

  ret->num++;
  return 1;
  }
