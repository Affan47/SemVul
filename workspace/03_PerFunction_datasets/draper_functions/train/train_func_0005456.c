gd_mfield_list_by_type(DIRFILE* D, const char* parent,
    gd_entype_t type) gd_nothrow
{
  int i, index = -1;
  unsigned int n;
  char **fl;
  gd_entry_t *P;
  struct _gd_private_entry *e;
  size_t offs;

  dtrace("%p, \"%s\", %x", D, parent, type);

  if (D->flags & GD_INVALID) {
    _GD_SetError(D, GD_E_BAD_DIRFILE, 0, NULL, 0, NULL);
    dreturn("%p", NULL);
    return NULL;
  }

  _GD_ClearError(D);

  P = _GD_FindField(D, parent, D->entry, D->n_entries, NULL);

  if (P == NULL || P->e->n_meta == -1) {
    _GD_SetError(D, GD_E_BAD_CODE, 0, NULL, 0, parent);
    dreturn("%p", NULL);
    return NULL;
  }

  e = P->e;
  offs = strlen(P->field) + 1;

  n = gd_nmfields_by_type(D, parent, type);

  if (D->error) {
    dreturn("%p", NULL);
    return NULL;
  }

  if (n == 0) {
    dreturn("%p", zero_list);
    return zero_list;
  }


  for (i = 0; i < GD_N_ENTYPES; ++i)
    if (_gd_entype_index[i] == type) {
      index = i;
      break;
    }

  if (index == -1) {
    _GD_InternalError(D);
    dreturn("%p", NULL);
    return NULL;
  }

  fl = (char **)realloc(e->type_list[index], sizeof(const char*) * (n + 1));

  if (fl == NULL) {
    _GD_SetError(D, GD_E_ALLOC, 0, NULL, 0, NULL);
    dreturn("%p", NULL);
    return NULL;
  }

  for (i = n = 0; i < e->n_meta; ++i) {
    if (e->p.meta_entry[i]->field_type == type)
      fl[n++] = e->p.meta_entry[i]->field + offs;
  }
  fl[n] = NULL;

  e->type_list[index] = fl;

  dreturn("%p", e->type_list[index]);
  return (const char **)e->type_list[index];
}
