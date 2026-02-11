interpret_global_option (const string& arg)
{
  interpret_entry();

  ECA_LOG_MSG(ECA_LOGGER::system_objects, "Interpreting global option \"" + arg + "\".");
  if (istatus_rep == false) interpret_general_option(arg);
  if (istatus_rep == false) interpret_processing_control(arg);
  if (istatus_rep == false) interpret_chains(arg);

  interpret_exit(arg);
}
