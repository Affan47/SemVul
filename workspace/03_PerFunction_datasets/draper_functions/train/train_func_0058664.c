interpret_options(const std::vector<string>& opts)
{
  int optcount = static_cast<int>(opts.size());
  int global_matches = 0;
  int other_matches = 0;

  interpret_set_result(true, "");


  std::vector<string>::const_iterator p = opts.begin();
  while(p != opts.end()) {
    interpret_global_option(*p);


    if (interpret_match_found() == true &&
	!((*p)[0] == '-' && (*p)[1] == 'a')) global_matches++;

    ++p;
  }

  if (csetup_repp->chains.size() == 0) csetup_repp->add_default_chain();


  p = opts.begin();
  while(p != opts.end()) {
    interpret_object_option(*p);
    if (interpret_match_found() == true) {
      other_matches++;
      if (interpret_result() != true) {

	break;
      }
    }
    else {

      int dlevel = ECA_LOGGER::instance().get_log_level_bitmask();
      ECA_LOGGER::instance().disable();
      interpret_global_option(*p);
      ECA_LOGGER::instance().set_log_level_bitmask(dlevel);
      if (interpret_match_found() != true) {
	interpret_set_result(false, string("Invalid argument, unable to parse: \"") + *p + "\"");
	break;
      }
      else {
	if (interpret_result() != true) {

	  break;
	}
      }
    }
    ++p;
  }

  if (other_matches + global_matches != optcount) {
    ECA_LOG_MSG(ECA_LOGGER::info,
		string("WARNING: Only ") +
		kvu_numtostr(other_matches) +
		"+" +
		kvu_numtostr(global_matches) +
		" of the expected " +
		kvu_numtostr(optcount) +
		" parameters were recognized successfully.");
  }
}
