closeHive(struct hive *hdesc)
{


  if (hdesc->state & HMODE_OPEN) {
    close(hdesc->filedesc);
  }
  FREE(hdesc->filename);
  FREE(hdesc->buffer);
  FREE(hdesc);

}
