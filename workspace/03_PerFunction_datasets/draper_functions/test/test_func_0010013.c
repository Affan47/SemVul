get_lang_bitmap (const char *gtfile)
{

  if (gtfile == this_file)

    return (((lang_bitmap)1) << num_lang_dirs) - 1;
  else
    {
      lang_bitmap n = 0;
      int i;
      for (i = -(int) sizeof (lang_bitmap); i < 0; i++)
	n = (n << CHAR_BIT) + (unsigned char)gtfile[i];
      return n;
    }
}
