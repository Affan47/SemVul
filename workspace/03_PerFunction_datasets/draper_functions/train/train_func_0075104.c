sequence_dtor(stp_sequence_t *sequence)
{
  invalidate_auxilliary_data(sequence);
  if (sequence->data)
    stp_free(sequence->data);
  memset(sequence, 0, sizeof(stp_sequence_t));
}
