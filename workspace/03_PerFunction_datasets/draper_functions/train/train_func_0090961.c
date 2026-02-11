knuth_morris_pratt_multibyte (const char *haystack, const char *needle,
			      const char **resultp)
{
  size_t m = mbslen (needle);
  mbchar_t *needle_mbchars;
  size_t *table;


  char *memory = (char *) malloca (m * (sizeof (mbchar_t) + sizeof (size_t)));
  if (memory == NULL)
    return false;
  needle_mbchars = (mbchar_t *) memory;
  table = (size_t *) (memory + m * sizeof (mbchar_t));


  {
    mbui_iterator_t iter;
    size_t j;

    j = 0;
    for (mbui_init (iter, needle); mbui_avail (iter); mbui_advance (iter), j++)
      mb_copy (&needle_mbchars[j], &mbui_cur (iter));
  }


  {
    size_t i, j;

    table[1] = 1;
    j = 0;
    for (i = 2; i < m; i++)
      {
	mbchar_t *b = &needle_mbchars[i - 1];

	for (;;)
	  {
	    if (mb_equal (*b, needle_mbchars[j]))
	      {
		table[i] = i - ++j;
		break;
	      }
	    if (j == 0)
	      {
		table[i] = i;
		break;
	      }
	    j = j - table[j];
	  }
      }
  }


  {
    size_t j;
    mbui_iterator_t rhaystack;
    mbui_iterator_t phaystack;

    *resultp = NULL;
    j = 0;
    mbui_init (rhaystack, haystack);
    mbui_init (phaystack, haystack);

    while (mbui_avail (phaystack))
      if (mb_equal (needle_mbchars[j], mbui_cur (phaystack)))
	{
	  j++;
	  mbui_advance (phaystack);
	  if (j == m)
	    {

	      *resultp = mbui_cur_ptr (rhaystack);
	      break;
	    }
	}
      else if (j > 0)
	{

	  size_t count = table[j];
	  j -= count;
	  for (; count > 0; count--)
	    {
	      if (!mbui_avail (rhaystack))
		abort ();
	      mbui_advance (rhaystack);
	    }
	}
      else
	{

	  if (!mbui_avail (rhaystack))
	    abort ();
	  mbui_advance (rhaystack);
	  mbui_advance (phaystack);
	}
  }

  freea (memory);
  return true;
}
