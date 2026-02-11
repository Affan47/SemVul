notify_file_flags_changed(const DjVuFile *file,
                                           long mask, long)
{
  if (mask & (DjVuFile::ALL_DATA_PRESENT | DjVuFile::DATA_PRESENT |
              DjVuFile::DECODE_FAILED | DjVuFile::DECODE_STOPPED |
              DjVuFile::STOPPED | DjVuFile::DECODE_STOPPED ))
    {
      GMonitorLock lock(&monitor);
      monitor.signal();
    }
}
