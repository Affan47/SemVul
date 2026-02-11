InitializeImpl(const OptionsList& options,
      const std::string& prefix)
  {
    Index enum_int;

    options.GetNumericValue("sigma_max", sigma_max_, prefix);
    options.GetNumericValue("sigma_min", sigma_min_, prefix);

    options.GetEnumValue("quality_function_norm_type", enum_int, prefix);
    quality_function_norm_ = NormEnum(enum_int);
    options.GetEnumValue("quality_function_centrality", enum_int, prefix);
    quality_function_centrality_ = CentralityEnum(enum_int);
    options.GetEnumValue("quality_function_balancing_term", enum_int, prefix);
    quality_function_balancing_term_ = BalancingTermEnum(enum_int);
    options.GetIntegerValue("quality_function_max_section_steps",
                            quality_function_max_section_steps_, prefix);
    options.GetNumericValue("quality_function_section_sigma_tol",
                            quality_function_section_sigma_tol_, prefix);
    options.GetNumericValue("quality_function_section_qf_tol",
                            quality_function_section_qf_tol_, prefix);

    initialized_ = false;

    return true;
  }
