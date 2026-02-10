ml_gdome_mevnt_compare(value v1, value v2)
{
  CAMLparam2(v1,v2);
  GdomeMutationEvent* obj1_ = MutationEvent_val(v1);
  GdomeMutationEvent* obj2_ = MutationEvent_val(v2);
  CAMLreturn((int) (obj1_ - obj2_));
}
