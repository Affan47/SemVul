_GD_DoConst(DIRFILE *D, const gd_entry_t *E, off64_t first,
    size_t len, gd_type_t return_type, void *data_out)
{
  gd_type_t type;

  dtrace("%p, %p, %lli, %zu, 0x%x, %p", D, E, first, len, return_type,
      data_out);

  type = _GD_ConstType(D, E->EN(scalar,const_type));
  _GD_ConvertType(D, (char *)E->e->u.scalar.d + first * GD_SIZE(type), type,
      data_out, return_type, len);

  if (D->error) {
    dreturn("%i", 0);
    return 0;
  }

  dreturn("%i", 1);
  return 1;
}
