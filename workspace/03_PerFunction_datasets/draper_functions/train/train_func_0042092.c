_dvb_sub_parse_object_segment (DvbSub * dvb_sub, guint16 page_id, guint8 * buf,
    gint buf_size)
{
  const guint8 *buf_end = buf + buf_size;
  guint object_id;
  DVBSubObject *object;

  guint8 coding_method, non_modifying_color;

  object_id = GST_READ_UINT16_BE (buf);
  buf += 2;

  object = get_object (dvb_sub, object_id);

  GST_DEBUG ("OBJECT: a new object segment has occurred for object_id = %u",
      object_id);

  if (!object) {
    GST_WARNING ("Nothing known about object with ID %u yet, bailing out",
        object_id);
    return;
  }

  coding_method = ((*buf) >> 2) & 3;
  non_modifying_color = ((*buf++) >> 1) & 1;

  if (coding_method == 0) {
    const guint8 *block;
    DVBSubObjectDisplay *display;
    guint16 top_field_len, bottom_field_len;

    top_field_len = GST_READ_UINT16_BE (buf);
    buf += 2;
    bottom_field_len = GST_READ_UINT16_BE (buf);
    buf += 2;

    if (buf + top_field_len + bottom_field_len > buf_end) {
      GST_WARNING ("Field data size too large");
      return;
    }


    for (display = object->display_list; display;
        display = display->object_list_next) {
      block = buf;

      GST_DEBUG ("OBJECT: parsing top and bottom part of object id %d; "
          "top_field_len = %u, bottom_field_len = %u",
          display->object_id, top_field_len, bottom_field_len);

      _dvb_sub_parse_pixel_data_block (dvb_sub, display, block, top_field_len,
          TOP_FIELD, non_modifying_color);

      if (bottom_field_len > 0)
        block = buf + top_field_len;
      else
        bottom_field_len = top_field_len;

      _dvb_sub_parse_pixel_data_block (dvb_sub, display, block,
          bottom_field_len, BOTTOM_FIELD, non_modifying_color);
    }

  } else if (coding_method == 1) {
    GST_FIXME ("'a string of characters' coding method not supported yet!");
  } else {
    GST_WARNING ("Unknown object coding 0x%x", coding_method);
  }
}
