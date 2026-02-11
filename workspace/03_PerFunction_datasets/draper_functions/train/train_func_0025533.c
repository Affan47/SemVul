unit_types_free(void)
{
  unit_type_iterate(punittype) {
    unit_type_free(punittype);
  } unit_type_iterate_end;
}
