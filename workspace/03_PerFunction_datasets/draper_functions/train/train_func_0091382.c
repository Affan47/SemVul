gd_framenum_subset64(DIRFILE* D, const char* field_code_in,
    double value, off64_t field_start, off64_t field_end)
{
  double frame = NAN;
  gd_entry_t* entry;
  char* field_code;
  int repr = GD_REPR_NONE;
  gd_spf_t spf;

  dtrace("%p, \"%s\", %g, %lli, %lli", D, field_code_in, value, field_start,
      field_end);

  if (D->flags & GD_INVALID) {
    _GD_SetError(D, GD_E_BAD_DIRFILE, 0, NULL, 0, NULL);
    dreturn("%g", frame);
    return frame;
  }

  _GD_ClearError(D);

  entry = _GD_FindFieldAndRepr(D, field_code_in, &field_code, &repr, NULL, 1);

  if (D->error) {
    dreturn("%g", frame);
    return frame;
  }

  if (_GD_NativeType(D, entry, repr) & GD_COMPLEX)
    _GD_SetError(D, GD_E_DOMAIN, GD_E_DOMAIN_COMPLEX, NULL, 0, NULL);

  if (field_code != field_code_in)
    free(field_code);

  if (D->error) {
    dreturn("%g", frame);
    return frame;
  }

  spf = _GD_GetSPF(D, entry);
  if (field_start == 0)
    field_start = D->fragment[entry->fragment_index].frame_offset * spf;
  else
    field_start *= spf;

  if (field_end == 0)
    field_end = (gd_nframes64(D) + 1) * spf - 1;
  else
    field_end = field_end * spf - 1;

  if (field_end - field_start < 2)
    _GD_SetError(D, GD_E_DOMAIN, GD_E_DOMAIN_EMPTY, NULL, 0, NULL);

  if (!D->error)
    frame = _GD_GetIndex(D, entry, repr, value, field_start, field_end) / spf;

  dreturn("%g", frame);
  return frame;
}
