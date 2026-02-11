write_word_block(unsigned count, WORD value)
{
  while (count != 0)
    {
      write_big_endian_word(value);
      count--;
    }
}
