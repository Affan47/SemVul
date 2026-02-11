set_child_start_position(const ECA_AUDIO_TIME& v)
{
  if (is_open() == true &&
      child()->supports_seeking_sample_accurate() != true) {
    ECA_LOG_MSG(ECA_LOGGER::errors,
		"ERROR: object \"" + child()->label() +
		"\" does not support sample accurate seeking, unable to set start position.");
    return;
  }

  child_start_pos_rep = v;
}
