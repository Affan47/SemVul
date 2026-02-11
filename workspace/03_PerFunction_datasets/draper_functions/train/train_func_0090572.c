check_string (gint filter, const gchar *str)
{
  gboolean success = FALSE;
  gint ret;

  if ((filter == GST_FILTER_IP) ||
      (filter == GST_FILTER_IPV4) ||
      (filter == GST_FILTER_IPV6))
    {
      ret = gst_filter_check_ip_address (str);

      if (filter == GST_FILTER_IP)
        success = ((ret == GST_ADDRESS_INCOMPLETE) ||
                   (ret == GST_ADDRESS_IPV4_INCOMPLETE) ||
                   (ret == GST_ADDRESS_IPV4) ||
                   (ret == GST_ADDRESS_IPV6_INCOMPLETE) ||
                   (ret == GST_ADDRESS_IPV6));
      else if (filter == GST_FILTER_IPV4)
        success = ((ret == GST_ADDRESS_INCOMPLETE) ||
                   (ret == GST_ADDRESS_IPV4_INCOMPLETE) ||
                   (ret == GST_ADDRESS_IPV4));
      else if (filter == GST_FILTER_IPV6)
        success = ((ret == GST_ADDRESS_INCOMPLETE) ||
                   (ret == GST_ADDRESS_IPV6_INCOMPLETE) ||
                   (ret == GST_ADDRESS_IPV6));
    }
  else if (filter == GST_FILTER_PHONE)
    success = (strspn (str, "0123456789abcdABCD,#*") == strlen (str));

  return success;
}
