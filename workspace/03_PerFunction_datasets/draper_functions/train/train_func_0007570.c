start_servers(void)
{
  if (csetup_repp->double_buffering() == true) {
    csetup_repp->pserver_repp->start();
    ECA_LOG_MSG(ECA_LOGGER::user_objects, "prefilling i/o buffers.");
    csetup_repp->pserver_repp->wait_for_full();
    ECA_LOG_MSG(ECA_LOGGER::user_objects, "i/o buffers prefilled.");
  }

  if (use_midi_rep == true) {
    csetup_repp->midi_server_repp->start();
  }
}
