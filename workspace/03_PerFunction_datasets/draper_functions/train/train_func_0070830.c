set_log_level(ECA_LOGGER::Msg_level_t level, bool enabled)
{
  if (enabled == true) {
    debug_value_rep |= level;
  }
  else {
    debug_value_rep &= ~level;
  }
}
