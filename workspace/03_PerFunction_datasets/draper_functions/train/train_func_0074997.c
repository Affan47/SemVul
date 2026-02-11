set_parameter(int param,
			     string value)
{
  ECA_LOG_MSG(ECA_LOGGER::user_objects,
	      AUDIO_IO::parameter_set_to_string(param, value));
  if (param == 1) set_label(value);
}
