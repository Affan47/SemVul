preprocess_options(std::vector<string>& opts) const
{
  std::vector<string>::iterator p = opts.begin();
  while(p != opts.end()) {


    if (p->size() > 0 && (*p)[0] != '-') {

      ECA_LOG_MSG(ECA_LOGGER::info, "NOTE: Interpreting option " +
		    *p +
		    " as -i:" +
		    *p +
		    ".");
      *p = "-i:" + *p;
    }
    ++p;
  }
}
