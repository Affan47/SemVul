xsh_pfits_set_wavesoltype( cpl_propertylist * plist, const char* value)
{
  XSH_REGDEBUG("writing keyword %s = %s", XSH_WAVESOLTYPE, value);
  check_msg (cpl_propertylist_update_string (plist, XSH_WAVESOLTYPE, value),
             "Error writing keyword '%s'", XSH_WAVESOLTYPE);
  cleanup:
    return;
}
