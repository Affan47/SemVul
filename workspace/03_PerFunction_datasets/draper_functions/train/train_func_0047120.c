fork_input_process(void)
{
  ECA_LOG_MSG(ECA_LOGGER::user_objects, AAC_FORKED_INTERFACE::default_input_cmd);

  set_fork_command(AAC_FORKED_INTERFACE::default_input_cmd);
  set_fork_file_name(label());

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
