fax_rx_phase(int internal)
{
  fprintf(stderr,"entering phase-in mode\n");
  sync_phase(1);
  fax_state = FAX_PHAS;
  if (internal)
    mode_notify(fax_state);
}
