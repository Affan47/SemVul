import_data_record(itracku_data_record* d)
{
  int result = 0;

  if (!itracku_is_valid_data_record(d)) {
    result = 0;
  } else {
    if (fbackup) {
      if ((gbuint32)le_read32(d->creation_time) > backup_last_creation_time) {
        backup_last_creation_time = le_read32(d->creation_time);
        gbfwrite(d, sizeof(*d), 1, fbackup);
        result = -1;
      } else {
        result = (only_new == NULL);
      }
    } else {
      result = -1;
    }
  }
  if (result) {
    ++new_waypoint_count;
  }
  return result;
}
