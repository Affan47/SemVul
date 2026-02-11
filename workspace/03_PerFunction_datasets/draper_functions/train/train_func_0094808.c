iso7816_apdu_direct (int slot, const void *apdudata, size_t apdudatalen,
                     int handle_more,
                     unsigned char **result, size_t *resultlen)
{
  int sw;

  if (!result || !resultlen)
    return gpg_error (GPG_ERR_INV_VALUE);
  *result = NULL;
  *resultlen = 0;

  sw = apdu_send_direct (slot, 0, apdudata, apdudatalen, handle_more,
                         result, resultlen);
  if (!sw)
    {
      if (*resultlen < 2)
        sw = SW_HOST_GENERAL_ERROR;
      else
        {
          sw = ((*result)[*resultlen-2] << 8) | (*result)[*resultlen-1];
          (*resultlen)--;
          (*resultlen)--;
        }
    }
  if (sw != SW_SUCCESS)
    {

      xfree (*result);
      *result = NULL;
      *resultlen = 0;
    }
  return map_sw (sw);
}
