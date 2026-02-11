fullstr() const {

    if (*this)
      return URL::fullstr();
    else if (urloptions.empty())
      return name;
    else
      return name + ';' + OptionString(urloptions, ';');
  }
