check_return_type (type onstack)
{
  type rt = compute_return_type (vfy_get_signature (vfr->current_method));
  if (! types_compatible (&rt, &onstack))
    verify_fail ("incompatible return type");
}
