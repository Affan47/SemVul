fork_output_process(void)
{
  ECA_LOG_MSG(ECA_LOGGER::info, "Starting to encode " + label() + " with vorbize.");
  string command = OGG_VORBIS_INTERFACE::default_output_cmd;


  if (command.find("%B") != string::npos) {
    command.replace(command.find("%B"), 2, kvu_numtostr((long int)(bitrate_rep / 1000)));
  }

  set_fork_command(command);
  set_fork_file_name(label());

  set_fork_bits(bits());
  set_fork_channels(channels());
  set_fork_sample_rate(samples_per_second());

  fork_child_for_write();
  if (child_fork_succeeded() == true) {
    filedes_rep = file_descriptor();
  }
  else {
    filedes_rep = 0;
  }
}
