option(Fl_Option opt, bool val)
{
  if (opt<0 || opt>=OPTION_LAST)
    return;
  if (!options_read_) {

    option(opt);
  }
  options_[opt] = val;
}
