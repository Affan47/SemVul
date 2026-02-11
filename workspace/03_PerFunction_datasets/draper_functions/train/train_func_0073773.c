serpent_key_prepare (const byte *key, unsigned int key_length,
		     serpent_key_t key_prepared)
{
  int i;


  memcpy (key_prepared, key, key_length);
  key_length /= 4;
#ifdef WORDS_BIGENDIAN
  for (i = 0; i < key_length; i++)
    key_prepared[i] = byte_swap_32 (key_prepared[i]);
#else
  i = key_length;
#endif
  if (i < 8)
    {


      key_prepared[i] = 0x00000001;

      for (i++; i < 8; i++)
	key_prepared[i] = 0;
    }
}
