interpret_general_option (const std::string& argu)
{
  if (argu.size() < 2) return 0;
  if (argu[0] != '-') return 0;

  switch(argu[1]) {
  case 'd':
    {
      if (argu.size() > 2 && argu[2] == ':') {

	ECA_LOGGER::instance().set_log_level_bitmask(atoi(kvu_get_argument_number(1, argu).c_str()));
      }
      else {


	ECA_LOGGER::instance().set_log_level_bitmask(0);
	ECA_LOGGER::instance().set_log_level(ECA_LOGGER::errors, 1);
	ECA_LOGGER::instance().set_log_level(ECA_LOGGER::info, 1);
	ECA_LOGGER::instance().set_log_level(ECA_LOGGER::subsystems, 1);
	ECA_LOGGER::instance().set_log_level(ECA_LOGGER::module_names, 1);
	ECA_LOGGER::instance().set_log_level(ECA_LOGGER::user_objects, 1);
	ECA_LOGGER::instance().set_log_level(ECA_LOGGER::eiam_return_values, 1);

	if (argu.size() > 2 && argu[2] == 'd') {

	  ECA_LOGGER::instance().set_log_level(ECA_LOGGER::system_objects, 1);

	  if (argu.size() > 3 && argu[3] == 'd') {

	    ECA_LOGGER::instance().set_log_level(ECA_LOGGER::functions, 1);
	    ECA_LOGGER::instance().set_log_level(ECA_LOGGER::continuous, 1);
	  }
	}
      }

      MESSAGE_ITEM mtempd;
      mtempd << "Set debug level to: " << ECA_LOGGER::instance().get_log_level_bitmask();
      ECA_LOG_MSG(ECA_LOGGER::info, mtempd.to_string());
      break;
    }

  case 'R':
    {
      string tname = kvu_get_argument_number(1, argu);


      if (argu.size() > 2 && argu[2] == ':') {
	ECA_RESOURCES::rc_override_file = tname;
	cs_defaults_set_rep = false;
	ECA_LOG_MSG(ECA_LOGGER::info,
		    "Using resource file \"" +
		    tname +
		    "\". Disabling use of global/user resource files.");
      }
    }
    break;

  case 'q':
    ECA_LOGGER::instance().disable();
    break;

  default: { }
  }

  return 0;
}
