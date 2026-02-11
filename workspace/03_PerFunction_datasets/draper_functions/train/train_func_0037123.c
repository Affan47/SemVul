dio_put_bool32(struct data_out *dout, bool value)
{
  if (value != TRUE && value != FALSE) {
    log_error("Trying to put a non-boolean: %d", (int) value);
    value = FALSE;
  }

  dio_put_uint32(dout, value ? 1 : 0);
}
