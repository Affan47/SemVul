strstr (const ACE_NS_String &s) const
{
  ACE_TRACE ("ACE_NS_String::strstr");

  if (this->len_ < s.len_)

    return -1;
  else if (this->len_ == s.len_)

    return *this == s ? 0 : -1;
  else
    {

      const size_t len = (this->len_ - s.len_) / sizeof (ACE_WCHAR_T);
      const size_t pat_len = s.len_ / sizeof (ACE_WCHAR_T) - 1;

      for (size_t i = 0; i <= len; ++i)
        {
          size_t j;

          for (j = 0; j < pat_len; ++j)
            if (this->rep_[i + j] != s.rep_[j])
              break;

          if (j == pat_len)

            return ACE_Utils::truncate_cast<int> (i);
        }

      return -1;
    }
}
