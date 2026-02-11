po_message_is_range (po_message_t message, int *minp, int *maxp)
{
  message_ty *mp = (message_ty *) message;

  if (has_range_p (mp->range))
    {
      *minp = mp->range.min;
      *maxp = mp->range.max;
      return 1;
    }
  else
    return 0;
}
