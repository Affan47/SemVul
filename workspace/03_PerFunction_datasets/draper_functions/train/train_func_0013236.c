type_to_array (type *t)
{
  type at;
  vfy_jclass k;

  if (t->key != reference_type)
    verify_fail ("internal error in type::to_array()");

  k = ref_getclass (t->klass);
  init_type_from_class (&at, vfy_get_array_class (k));
  return at;
}
