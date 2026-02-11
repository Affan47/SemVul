get_code()
{
  unsigned long code;

  while (bits_left < code_length)
    {
      bits_buffer |= ((*input++) << bits_left);
      bits_left += 8;
    }

  code = bits_buffer & ((1 << code_length) - 1);

  bits_buffer >>= code_length;
  bits_left -= code_length;

  return code;
}
