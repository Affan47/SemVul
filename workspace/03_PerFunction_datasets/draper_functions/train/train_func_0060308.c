refs_equal (ref_intersection *ref1, ref_intersection *ref2)
{
  if (! ref1->is_resolved && ! ref2->is_resolved
      && vfy_strings_equal (ref1->data.name, ref2->data.name))
    return true;
  if (! ref1->is_resolved)
    resolve_ref (ref1);
  if (! ref2->is_resolved)
    resolve_ref (ref2);
  return ref1->data.klass == ref2->data.klass;
}
