utf162ucs4 (const ACEXML_UTF16 *src,
                               size_t len,
                               ACEXML_UCS4 &dst)
{
  if (src == 0)
    {
      return ACEXML_INVALID_ARGS;
    }

  size_t forward = 1;
  if (*src >= 0xDC00 && *src < 0xE000)
    {
      if (len < 2)
        {
          return ACEXML_END_OF_SOURCE;
        }

      return ACEXML_Transcoder::surrogate2ucs4 (*src,
                                                *(src+1),
                                                dst);
    }
  else
    {
      if (len < 1)
        {
          return ACEXML_END_OF_SOURCE;
        }

      dst = *src;
    }

  return ACE_Utils::truncate_cast<int> (forward);
}
