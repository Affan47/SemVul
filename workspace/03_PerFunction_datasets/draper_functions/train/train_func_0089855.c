pusb_read_int_from_ups(UPSINFO *ups, int ci, int *value)
{
   USB_VALUE val;

   if (!pusb_get_value(ups, ci, &val))
      return false;

   *value = val.iValue;
   return true;
}
