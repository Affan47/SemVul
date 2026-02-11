stp_sequence_set_data(stp_sequence_t *sequence,
		      size_t size, const double *data)
{
  CHECK_SEQUENCE(sequence);
  sequence->size = size;
  if (sequence->data)
    stp_free(sequence->data);
  sequence->data = stp_zalloc(sizeof(double) * size);
  memcpy(sequence->data, data, (sizeof(double) * size));
  invalidate_auxilliary_data(sequence);
  sequence->recompute_range = 1;
  return 1;
}
