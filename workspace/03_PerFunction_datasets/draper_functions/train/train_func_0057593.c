quovadis_writewpt(waypoint *wpt)
{
  struct record *rec;
  int	i;

  if (current_rec == NULL) {
    gbuint8 dummy = 0;

    pdb_write_rec(file_out, 0, 0, ct++, &dummy, 1);

    current_rec = (gbuint8 *) xcalloc(MAXCHUNKSIZE, 1);
    rec_index = 0;
    rec_ptr = current_rec;
  }

  rec = (struct record *) xcalloc(sizeof(*rec),1);

  be_write32(&rec->longitude, (unsigned int)((wpt->longitude +
             180.0) * 1000000.0));
  be_write32(&rec->latitude, (unsigned int)((90.0 - wpt->latitude) * 1000000.0));
  if (wpt->shortname) {
    strncpy(rec->name, wpt->shortname, 32);
    rec->name[31] = '\0';
  } else {
    rec->name[0] = '\0';
  }
  be_write16(&rec->icon_bitmap, wpt_to_icon(wpt->gc_data->type));
  be_write32(&rec->note_id, 0);
  rec->name_scale = DEFAULT_NAME_SCALE;
  rec->icon_scale = DEFAULT_ICON_SCALE;
  for (i = 0; i < 7; i++) {
    rec->reserved[i] = 0;
  }

  memcpy(rec_ptr, rec, sizeof(*rec));
  rec_ptr += sizeof(*rec);
  rec_index += 1;
  xfree(rec);

  if (rec_index == MAXRECORDS) {
    fatal(MYNAME ": cannot store more than %lu records at this time.\n",
          (unsigned long) MAXRECORDS);
  }
}
