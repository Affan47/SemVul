stp_curve_set_point(stp_curve_t *curve, size_t where, double data)
{
  CHECK_CURVE(curve);
  if (where >= get_point_count(curve))
    return 0;
  curve->gamma = 0.0;

  if (curve->piecewise)
    return 0;
  if ((stp_sequence_set_point(curve->seq, where, data)) == 0)
    return 0;
  if (where == 0 && curve->wrap_mode == STP_CURVE_WRAP_AROUND)
    if ((stp_sequence_set_point(curve->seq,
				get_point_count(curve), data)) == 0)
      return 0;
  invalidate_auxiliary_data(curve);
  return 1;
}
