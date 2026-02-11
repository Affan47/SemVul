stp_sequence_set_point(stp_sequence_t *sequence, size_t where,
		       double data)
{
  CHECK_SEQUENCE(sequence);

  if (where >= sequence->size || ! isfinite(data) ||
      data < sequence->blo || data > sequence->bhi)
    return 0;

  if (sequence->recompute_range == 0 && (data < sequence->rlo ||
					 data > sequence->rhi ||
					 sequence->data[where] == sequence->rhi ||
					 sequence->data[where] == sequence->rlo))
    sequence->recompute_range = 1;

  sequence->data[where] = data;
  invalidate_auxilliary_data(sequence);
  return 1;
}
