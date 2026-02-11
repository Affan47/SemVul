printf_count (STREAM *stream, struct printf_info *const pinfo, union printf_arg const *args)
{
  if (pinfo->is_char)
    *(char *) (args->pa_pointer) = pinfo->count;

  else if (pinfo->is_short)
    *(short *) (args->pa_pointer) = pinfo->count;

  else if (pinfo->is_long)
    *(long *) (args->pa_pointer) = pinfo->count;

  else if (pinfo->is_long_double)
    *(intmax_t *) (args->pa_pointer) = pinfo->count;

  else
    *(int *) (args->pa_pointer) = pinfo->count;

  return 0;
}
