get_unicode_params (unsigned char *addr, int swap, unsigned int *start_offset,
		    int *real_utf16, unsigned int *extra_skip)
{

    biff_word16 word16;
    biff_word32 word32;
    int skip_1 = 0;
    int skip_2 = 0;
    unsigned char *p_string = addr;
    unsigned char mask = *p_string;


    p_string++;
    if ((mask & 0x01) == 0x01)
	*real_utf16 = 1;
    else
	*real_utf16 = 0;
    if ((mask & 0x04) == 0x04)
      {

	  memcpy (word32.bytes, p_string, 2);
	  if (swap)
	      swap32 (&word32);
	  skip_1 = word32.value;
	  p_string += 4;
      }
    if ((mask & 0x08) == 0x08)
      {

	  memcpy (word16.bytes, p_string, 2);
	  if (swap)
	      swap16 (&word16);
	  skip_2 = word16.value;
	  p_string += 2;
      }
    *start_offset = p_string - addr;
    *extra_skip = skip_1 + (skip_2 * 4);
}
