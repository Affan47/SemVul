_GD_ParsePhase(DIRFILE* D, char* in_cols[MAX_IN_COLS],
    int n_cols, const gd_entry_t* parent, const char* format_file, int line,
    int standards, int pedantic, int* is_dot)
{
  gd_entry_t *E;

  dtrace("%p, %p, %i, %p, \"%s\", %i, %i, %i, %p", D, in_cols, n_cols, parent,
      format_file, line, standards, pedantic, is_dot);

  if (n_cols < 4) {
    _GD_SetError(D, GD_E_FORMAT, GD_E_FORMAT_N_TOK, format_file, line, NULL);
    dreturn("%p", NULL);
    return NULL;
  }

  E = (gd_entry_t *)malloc(sizeof(gd_entry_t));
  if (E == NULL) {
    _GD_SetError(D, GD_E_ALLOC, 0, NULL, 0, NULL);
    dreturn("%p", NULL);
    return NULL;
  }
  memset(E, 0, sizeof(gd_entry_t));

  E->e = (struct _gd_private_entry *)malloc(sizeof(struct _gd_private_entry));
  if (E->e == NULL) {
    _GD_SetError(D, GD_E_ALLOC, 0, NULL, 0, NULL);
    free(E);
    dreturn("%p", NULL);
    return NULL;
  }
  memset(E->e, 0, sizeof(struct _gd_private_entry));

  E->field_type = GD_PHASE_ENTRY;
  E->in_fields[0] = NULL;
  E->e->entry[0] = NULL;

  E->field = _GD_ValidateField(parent, in_cols[0], standards, pedantic, is_dot);
  if (E->field == in_cols[0]) {
    _GD_SetError(D, GD_E_FORMAT, GD_E_FORMAT_BAD_NAME, format_file, line,
        in_cols[0]);
    E->field = NULL;
    _GD_FreeE(E, 1);
    dreturn("%p", NULL);
    return NULL;
  }

  E->in_fields[0] = strdup(in_cols[2]);

  if (E->field == NULL || E->in_fields[0] == NULL) {
    _GD_SetError(D, GD_E_ALLOC, 0, NULL, 0, NULL);
    _GD_FreeE(E, 1);
    E = NULL;
  }

  if ((E->scalar[0] = _GD_SetScalar(D, in_cols[3], &E->EN(phase,shift),
          GD_INT64, format_file, line, E->scalar_ind, NULL)) == NULL)
  {
    E->e->calculated = 1;
  }

  dreturn("%p", E);
  return E;
}
