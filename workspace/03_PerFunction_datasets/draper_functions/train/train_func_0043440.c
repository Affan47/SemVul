hu_find_infoval(info_lkp_t *hid2info, long value)
{
  info_lkp_t *info_lkp;

  upsdebugx(3, "hu_find_infoval: searching for value = %ld\n", value);

  for (info_lkp = hid2info; (info_lkp != NULL) &&
	 (strcmp(info_lkp->nut_value, "NULL")); info_lkp++) {

    if (info_lkp->hid_value == value) {
      upsdebugx(3, "hu_find_infoval: found %s (value: %ld)\n",
		info_lkp->nut_value, value);

      return info_lkp->nut_value;
    }
  }
  upsdebugx(3, "hu_find_infoval: no matching INFO_* value for this HID value (%ld)\n", value);
  return NULL;
}
