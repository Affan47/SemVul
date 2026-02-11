gd_alter_encoding(DIRFILE* D, unsigned long encoding, int fragment,
    int move)
{
  int i;

  dtrace("%p, %lu, %i, %i", D, (unsigned long)encoding, fragment, move);

  if (D->flags & GD_INVALID) {
    _GD_SetError(D, GD_E_BAD_DIRFILE, 0, NULL, 0, NULL);
    dreturn("%i", -1);
    return -1;
  }

  if ((D->flags & GD_ACCMODE) != GD_RDWR) {
    _GD_SetError(D, GD_E_ACCMODE, 0, NULL, 0, NULL);
    dreturn("%i", -1);
    return -1;
  }

  if (fragment < GD_ALL_FRAGMENTS || fragment >= D->n_fragment) {
    _GD_SetError(D, GD_E_BAD_INDEX, 0, NULL, 0, NULL);
    dreturn("%i", -1);
    return -1;
  }

  if (!_GD_EncodingUnderstood(encoding)) {
    _GD_SetError(D, GD_E_UNKNOWN_ENCODING, 0, NULL, 0, NULL);
    dreturn("%i", -1);
    return -1;
  }

  _GD_ClearError(D);

  if (fragment == GD_ALL_FRAGMENTS) {
    for (i = 0; i < D->n_fragment; ++i) {
      _GD_RecodeFragment(D, encoding, i, move);

      if (D->error)
        break;
    }
  } else
    _GD_RecodeFragment(D, encoding, fragment, move);

  dreturn("%i", (D->error) ? -1 : 0);
  return (D->error) ? -1 : 0;
}
