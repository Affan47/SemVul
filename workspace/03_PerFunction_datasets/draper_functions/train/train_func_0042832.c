gd_constants(DIRFILE* D, gd_type_t return_type) gd_nothrow
{
  unsigned int i, n;
  char* fl;

  dtrace("%p, 0x%x", D, return_type);

  if (D->flags & GD_INVALID) {
    _GD_SetError(D, GD_E_BAD_DIRFILE, 0, NULL, 0, NULL);
    dreturn("%p", NULL);
    return NULL;
  }

  _GD_ClearError(D);

  if (D->n_const == 0) {
    dreturn("%p", NULL);
    return NULL;
  }

  free(D->const_value_list);
  fl = (char *)_GD_Alloc(D, return_type, D->n_const);

  if (fl == NULL) {
    dreturn("%p", NULL);
    return NULL;
  }

  for (i = n = 0; i < D->n_entries; ++i) {
    if (D->entry[i]->field_type == GD_CONST_ENTRY &&
        D->entry[i]->e->n_meta != -1)
      if (_GD_DoField(D, D->entry[i], 0, 0, 1, return_type,
            fl + n++ * GD_SIZE(return_type)) != 1)
        break;
  }

  D->const_value_list = fl;

  dreturn("%p", D->error ? NULL : D->const_value_list);
  return D->error ? NULL : D->const_value_list;
}
