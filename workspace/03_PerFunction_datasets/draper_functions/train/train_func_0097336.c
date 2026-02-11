fsp_res_import (fsp_link *link, fs_segment segment,
                    int count, fs_resource buffer[])
{
  unsigned int k, serial_length = 0;

  for (k = 0; k < count; ++k) {
    serial_length+= ((28 + strlen(buffer[k].lex)) / 8);
  }

  int length = 8 + (8 * serial_length);

  unsigned char *out = message_new(FS_INSERT_RESOURCE, segment, length);
  unsigned char *record = out + FS_HEADER;

  memcpy(record, &count, sizeof(int));
  record += 8;

  for (k= 0; k < count; ++k) {
    unsigned int one_length = ((28 + strlen(buffer[k].lex)) / 8) * 8;

    memcpy(record, &buffer[k].rid, sizeof (fs_rid));
    memcpy(record + 8, &buffer[k].attr, sizeof (fs_rid));
    memcpy(record + 16, &one_length, sizeof(int));
    strcpy((char *) record + 20, buffer[k].lex);
    record += one_length;
  }

  fsp_write_replica(link, out, length);
  g_static_mutex_unlock (&link->mutex[segment]);

  free(out);
  return 0;
}
