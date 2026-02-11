cdk_armor_filter_use (cdk_stream_t inp)
{
  int c, check;
  int zipalgo;

  zipalgo = 0;
  c = cdk_stream_getc (inp);
  if (c == EOF)
    return 0;
  cdk_stream_seek (inp, 0);
  check = is_armored (c);
  if (check)
    {
      check = check_armor (inp, &zipalgo);
      if (zipalgo)
        _cdk_stream_set_compress_algo (inp, zipalgo);
    }
  return check;
}
