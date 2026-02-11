state_change_to_finished(void)
{
  if (finished_rep != true) {
    ECA_LOG_MSG_NOPREFIX(ECA_LOGGER::info, "");
    ECA_LOG_MSG(ECA_LOGGER::subsystems, "Engine - Processing finished");
  }
  finished_rep = true;
}
