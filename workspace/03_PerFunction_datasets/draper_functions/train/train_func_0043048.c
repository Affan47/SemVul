pattern_read_float_random_offsets(int fd, pattern_op_t op, void **state_p, float *percent_p)
{
  long storage;
  long index, *state = *state_p;
  pattern_result_t result = pr_continue;

  switch( op) {
  case op_init:
    state = *state_p = malloc(sizeof(long));
    *state = 0;
    break;

  case op_access:
    index = *state;
    read_from_random_offsets(fd, &storage, index, 1);
    index++;
    *state = index;

    *percent_p = 100.0 * index * sizeof(float) / file_size;

    if( index >= file_size / sizeof(float)) {
      result = pr_finished;
    }
    break;

  case op_fini:
    free( state);
    break;
  }

  return result;
}
