astr_vadd(struct astring *astr, size_t at,
                      const char *format, va_list ap)
{
  char *buffer;
  size_t buffer_size;
  size_t new_len;

  buffer = astr_buffer_get(&buffer_size);
  for (;;) {
    new_len = fc_vsnprintf(buffer, buffer_size, format, ap);
    if (new_len < buffer_size && (size_t) -1 != new_len) {
      break;
    }
    buffer = astr_buffer_grow(&buffer_size);
  }

  new_len += at + 1;

  astr_reserve(astr, new_len);
  fc_strlcpy(astr->str + at, buffer, astr->n_alloc - at);
}
