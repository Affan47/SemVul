topology_callback(unsigned value, struct connection *caller,
                              char *reject_msg, size_t reject_msg_len)
{
  if (map.server.mapsize == MAPSIZE_XYSIZE &&
      ((value & (TF_ISO)) != 0 || (value & (TF_HEX)) != 0) &&
      map.ysize % 2 != 0) {


    settings_snprintf(reject_msg, reject_msg_len,
                      _("For an isometric or hexagonal map the ysize must be "
                        "even."));
    return FALSE;
  }

  return TRUE;
}
