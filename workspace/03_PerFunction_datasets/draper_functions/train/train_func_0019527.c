zoneName(const struct tm *pTm_)
{
  if (pTm_==0)
    {
      return "";
    }

#if !defined(MS_STRUCT_TM_TZ)
  if (pTm_->tm_isdst<=0)
    {
      return tzname[0];
    }
  else
    {
      return tzname[1];
    }
#else
  return pTm_->tm_zone;
#endif
}
