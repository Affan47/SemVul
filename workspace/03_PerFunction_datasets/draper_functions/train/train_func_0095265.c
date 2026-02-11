gd_alter_carray(DIRFILE* D, const char* field_code, gd_type_t const_type,
    size_t array_len) gd_nothrow
{
  int ret;
  gd_entry_t N;

  dtrace("%p, \"%s\", 0x%x, %zu", D, field_code, const_type, array_len);

  if (D->flags & GD_INVALID) {
    _GD_SetError(D, GD_E_BAD_DIRFILE, 0, NULL, 0, NULL);
    dreturn("%i", -1);
    return -1;
  }

  N.field_type = GD_CARRAY_ENTRY;
  N.EN(scalar,const_type) = const_type;
  N.EN(scalar,array_len) = array_len;
  N.e = NULL;

  ret = _GD_Change(D, field_code, &N, 0);

  dreturn("%i", ret);
  return ret;
}
