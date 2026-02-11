gd_get_carray_slice(DIRFILE* D, const char *field_code_in,
    unsigned int start, size_t n, gd_type_t return_type, void *data_out)
gd_nothrow
{
  gd_entry_t *entry;
  char* field_code;
  int repr;

  dtrace("%p, \"%s\", %i, %zi, 0x%x, %p", D, field_code_in, (int)start, n,
      return_type, data_out);

  if (D->flags & GD_INVALID) {
    _GD_SetError(D, GD_E_BAD_DIRFILE, 0, NULL, 0, NULL);
    dreturn("%i", -1);
    return -1;
  }

  _GD_ClearError(D);

  entry = _GD_FindFieldAndRepr(D, field_code_in, &field_code, &repr, NULL, 1);

  if (D->error) {
    dreturn("%i", -1);
    return -1;
  }

  if (entry->field_type != GD_CARRAY_ENTRY)
    _GD_SetError(D, GD_E_BAD_FIELD_TYPE, GD_E_FIELD_BAD, NULL, 0, field_code);
  else if (start + n > entry->EN(scalar,array_len))
    _GD_SetError(D, GD_E_BOUNDS, 0, NULL, 0, NULL);
  else if (!D->error)
    _GD_DoField(D, entry, repr, start, n, return_type, data_out);

  if (field_code != field_code_in)
    free(field_code);

  if (D->error) {
    dreturn("%i", -1);
    return -1;
  }

  dreturn("%i", 0);
  return 0;
}
