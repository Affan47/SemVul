sort_slices_func_with_gate(gconstpointer a, gconstpointer b) {
  AmitkDataSet * slice_a = (AmitkDataSet *) a;
  AmitkDataSet * slice_b = (AmitkDataSet *) b;
  amide_time_t gate_time_a, gate_time_b;

  g_return_val_if_fail(AMITK_IS_DATA_SET(slice_a), -1);
  g_return_val_if_fail(AMITK_IS_DATA_SET(slice_b), 1);


  if ((slice_a->gate_num >= 0) && (slice_b->gate_num >=0)) {
    if (slice_a->gate_num < slice_b->gate_num)
      return -1;
    else if (slice_a->gate_num > slice_b->gate_num)
      return 1;
  }


  gate_time_a = amitk_data_set_get_gate_time(slice_a, 0);
  gate_time_b = amitk_data_set_get_gate_time(slice_b, 0);
  if (!REAL_EQUAL(gate_time_a, gate_time_b)) {
    if (gate_time_a < gate_time_b)
      return -1;
    else
      return 1;
  }


  return sort_slices_func(a,b);
}
