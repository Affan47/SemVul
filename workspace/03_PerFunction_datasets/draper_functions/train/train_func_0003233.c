notify_file_flags_changed(const DjVuFile *source,
                          long set_mask, long clr_mask)
{

  if (set_mask & (DjVuFile::DECODE_OK |
                  DjVuFile::DECODE_FAILED |
                  DjVuFile::DECODE_STOPPED ))
    {
      if (source->get_url() == decode_page_url)
        {
          decode_event_received=true;
          decode_event.set();
        }
    }
}
