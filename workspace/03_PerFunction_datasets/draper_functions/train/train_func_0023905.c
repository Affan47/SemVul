test_isotime2epoch (void)
{
  struct { const char *string; time_t expected; } array [] = {
    { "19700101T000001",  1 },
    { "19700101T235959",  86399 },
    { "19980815T143712",  903191832 },
    { "19700101T000000",  0 },
    { "19691231T235959",  INVALID },
    { "19000101T000000",  INVALID },
    { "",                 INVALID },
    { "19000101T00000",   INVALID },
    { "20010101t123456",  INVALID },
    { "20010101T123456",  978352496 },
    { "20070629T160000",  1183132800 },
    { "20070629T160000:",  1183132800 },
    { "20070629T160000,",  1183132800 },
    { "20070629T160000 ",  1183132800 },
    { "20070629T160000\n", 1183132800 },
    { "20070629T160000.",  INVALID },
    { NULL, 0 }
  };
  int idx;
  time_t val;
  gnupg_isotime_t tbuf;

  for (idx=0; array[idx].string; idx++)
    {
      val = isotime2epoch (array[idx].string);
      if (val != array[idx].expected )
        {
          fail (idx);
          if (verbose)
            fprintf (stderr, "string `%s' exp: %ld got: %ld\n",
                     array[idx].string, (long)array[idx].expected,
                     (long)val);
        }
      if (array[idx].expected != INVALID)
        {
          epoch2isotime (tbuf, val);
          if (strlen (tbuf) != 15)
            {
              if (verbose)
                fprintf (stderr, "string `%s', time-t %ld, revert: `%s'\n",
                         array[idx].string, (long)val, tbuf);
              fail (idx);
            }
          if (strncmp (array[idx].string, tbuf, 15))
            fail (idx);
        }
    }
}
