eprn_close_device(gx_device *device)
{
  eprn_Eprn *eprn = &((eprn_Device *)device)->eprn;

#ifdef EPRN_TRACE
  if_debug0(EPRN_TRACE_CHAR, "! eprn_close_device()...\n");
#endif

  if (eprn->scan_line.str != NULL) {
    gs_free(device->memory->non_gc_memory, eprn->scan_line.str, eprn->octets_per_line, sizeof(eprn_Octet),
      "eprn_close_device");
    eprn->scan_line.str = NULL;
  }
  if (eprn->next_scan_line.str != NULL) {
    gs_free(device->memory->non_gc_memory, eprn->next_scan_line.str, eprn->octets_per_line, sizeof(eprn_Octet),
      "eprn_close_device");
    eprn->next_scan_line.str = NULL;
  }

  return gdev_prn_close(device);
}
