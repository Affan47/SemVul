gnome_scanner_set_status (GnomeScanner *scanner, GnomeScannerStatus status)
{
  if (scanner->status != status) {
    scanner->status = status;
    g_signal_emit (scanner, signals[STATUS_CHANGED], 0);
  }
}
