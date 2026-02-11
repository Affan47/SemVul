camlidl_c2ml_coeff_struct_ap_coeff_t(struct ap_coeff_t * _c1, camlidl_ctx _ctx)
{
  value _v2;
  value _v3;
  value _v4;
  switch ((*_c1).discr) {
  case Scalar:
    _v3 = camlidl_c2ml_scalar_ap_scalar_t(&*(*_c1).val.scalar, _ctx);
    Begin_root(_v3)
      _v2 = camlidl_alloc_small(1, 0);
      Field(_v2, 0) = _v3;
    End_roots()
    break;
  case Interval:
    _v4 = camlidl_c2ml_interval_struct_ap_interval_t(&*(*_c1).val.interval, _ctx);
    Begin_root(_v4)
      _v2 = camlidl_alloc_small(1, 1);
      Field(_v2, 0) = _v4;
    End_roots()
    break;
  default:
    invalid_argument("struct ap_coeff_t: bad discriminant for union ");
  }
  return _v2;
}
