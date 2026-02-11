fork_input_process(void)
{
  string command = OGG_VORBIS_INTERFACE::default_input_cmd;


  if (command.find("%E") != string::npos) {
    string byteorder ("big");
    if (sample_endianess() == ECA_AUDIO_FORMAT::se_little) byteorder = "little";
    command.replace(command.find("%E"), 2, byteorder);
  }

  set_fork_command(command);
  set_fork_file_name(label());
  set_fork_pipe_name();
  fork_child_for_read();
  if (child_fork_succeeded() == true) {


    filedes_rep = file_descriptor();
    f1_rep = fdopen(filedes_rep, "r");
    if (f1_rep == 0) {
      finished_rep = true;
      triggered_rep = false;
    }
  }
  else
    f1_rep = 0;
}
