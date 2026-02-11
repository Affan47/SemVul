open_ct_reader (int port)
{
  int rc, reader;

  if (port < 0 || port > 0xffff)
    {
      log_error ("open_ct_reader: invalid port %d requested\n", port);
      return -1;
    }
  reader = new_reader_slot ();
  if (reader == -1)
    return reader;
  reader_table[reader].port = port;

  rc = CT_init (reader, (unsigned short)port);
  if (rc)
    {
      log_error ("apdu_open_ct_reader failed on port %d: %s\n",
                 port, ct_error_string (rc));
      reader_table[reader].used = 0;
      unlock_slot (reader);
      return -1;
    }


  rc = ct_activate_card (reader);
  if (rc)
    {
      reader_table[reader].atrlen = 0;
      rc = 0;
    }

  reader_table[reader].close_reader = close_ct_reader;
  reader_table[reader].reset_reader = reset_ct_reader;
  reader_table[reader].get_status_reader = ct_get_status;
  reader_table[reader].send_apdu_reader = ct_send_apdu;
  reader_table[reader].check_pinpad = NULL;
  reader_table[reader].dump_status_reader = ct_dump_reader_status;
  reader_table[reader].pinpad_verify = NULL;
  reader_table[reader].pinpad_modify = NULL;

  dump_reader_status (reader);
  unlock_slot (reader);
  return reader;
}
