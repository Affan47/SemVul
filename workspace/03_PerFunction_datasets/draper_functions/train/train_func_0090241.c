InitializeImpl(const OptionsList& options,
                                       const std::string& prefix)
  {
    options.GetNumericValue("sigma_max", sigma_max_, prefix);

    return true;
  }
