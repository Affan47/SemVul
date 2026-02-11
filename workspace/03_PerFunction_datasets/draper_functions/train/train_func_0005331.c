do_msg(ECA_LOGGER::Msg_level_t level, const std::string& module_name, const std::string& log_message)
{
  if (is_log_level_set(level) == true) {
    if (level == ECA_LOGGER::subsystems) {
      output_rep << "[* ";
    }
    else if (module_name.size() > 0 &&
	     is_log_level_set(ECA_LOGGER::module_names) == true &&
	     level != ECA_LOGGER::eiam_return_values) {
      output_rep << "("
		<< ECA_LOGGER_INTERFACE::filter_module_name(module_name)
		<< ") ";
    }

    output_rep << log_message;

    if (level == ECA_LOGGER::subsystems) {
      output_rep << " *]";
    }
    output_rep << std::endl;
  }
}
