gd_madd_linterp(DIRFILE* D, const char* parent,
    const char* field_code, const char* in_field, const char* table) gd_nothrow
{
  gd_entry_t L;
  int error;

  dtrace("%p, \"%s\", \"%s\", \"%s\", \"%s\"", D, field_code, parent, in_field,
      table);

  if (D->flags & GD_INVALID) {
    _GD_SetError(D, GD_E_BAD_DIRFILE, 0, NULL, 0, NULL);
    dreturn("%i", -1);
    return -1;
  }

  L.field = (char *)field_code;
  L.field_type = GD_LINTERP_ENTRY;
  L.in_fields[0] = (char *)in_field;
  L.EN(linterp,table) = (char *)table;
  L.fragment_index = 0;
  error = _GD_Add(D, &L, parent);

  dreturn("%i", error);
  return error;
}
