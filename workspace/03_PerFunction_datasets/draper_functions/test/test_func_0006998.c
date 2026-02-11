Vector_Next_Before(Vector vec, int n)
{
  int word_no;
  int bit_no;
  Vector start;
  Vector end;
  VecWord word;
  int bit;

  if (n <= vec_max_integer)
    {
      if (n < 0)
	return -1;

      word_no = Word_No(n);
      bit_no = Bit_No(n);

      end = vec + word_no;

      word = *end & ((1 << bit_no) - 1);
    }
  else
    {
      end = vec + vec_size - 1;
      word = *end;
    }


  start = vec;

  while (word == 0)
    {
      if (--end < start)
	return -1;

      word = *end;
    }

  bit = Most_Significant_Bit(word);
  n = Word_No_And_Bit_No(end - vec, bit);

  return n;
}
