RegisterOptions(SmartPtr<RegisteredOptions> roptions)
  {
    roptions->AddLowerBoundedNumberOption(
      "sigma_max",
      "Maximum value of the centering parameter.",
      0.0, true, 1e2,
      "This is the upper bound for the centering parameter chosen by the "
      "quality function based barrier parameter update. (Only used if option "
      "\"mu_oracle\" is set to \"quality-function\".)");
    roptions->AddLowerBoundedNumberOption(
      "sigma_min",
      "Minimum value of the centering parameter.",
      0.0, false, 1e-6,
      "This is the lower bound for the centering parameter chosen by the "
      "quality function based barrier parameter update. (Only used if option "
      "\"mu_oracle\" is set to \"quality-function\".)");
    roptions->AddStringOption4(
      "quality_function_norm_type",
      "Norm used for components of the quality function.",
      "2-norm-squared",
      "1-norm", "use the 1-norm (abs sum)",
      "2-norm-squared", "use the 2-norm squared (sum of squares)",
      "max-norm", "use the infinity norm (max)",
      "2-norm", "use 2-norm",
      "(Only used if option \"mu_oracle\" is set to \"quality-function\".)");
    roptions->AddStringOption4(
      "quality_function_centrality",
      "The penalty term for centrality that is included in quality function.",
      "none",
      "none", "no penalty term is added",
      "log", "complementarity * the log of the centrality measure",
      "reciprocal", "complementarity * the reciprocal of the centrality measure",
      "cubed-reciprocal", "complementarity * the reciprocal of the centrality measure cubed",
      "This determines whether a term is added to the quality function to "
      "penalize deviation from centrality with respect to complementarity.  The "
      "complementarity measure here is the xi in the Loqo update rule. (Only used if option "
      "\"mu_oracle\" is set to \"quality-function\".)");
    roptions->AddStringOption2(
      "quality_function_balancing_term",
      "The balancing term included in the quality function for centrality.",
      "none",
      "none", "no balancing term is added",
      "cubic", "Max(0,Max(dual_inf,primal_inf)-compl)^3",
      "This determines whether a term is added to the quality function that "
      "penalizes situations where the complementarity is much smaller "
      "than dual and primal infeasibilities. (Only used if option "
      "\"mu_oracle\" is set to \"quality-function\".)");
    roptions->AddLowerBoundedIntegerOption(
      "quality_function_max_section_steps",
      "Maximum number of search steps during direct search procedure "
      "determining the optimal centering parameter.",
      0, 8,
      "The golden section search is performed for the quality function based "
      "mu oracle. (Only used if option "
      "\"mu_oracle\" is set to \"quality-function\".)");
    roptions->AddBoundedNumberOption(
      "quality_function_section_sigma_tol",
      "Tolerance for the section search procedure determining "
      "the optimal centering parameter (in sigma space).",
      0.0, false, 1.0, true,
      1e-2,
      "The golden section search is performed for the quality function based "
      "mu oracle. (Only used if option "
      "\"mu_oracle\" is set to \"quality-function\".)");
    roptions->AddBoundedNumberOption(
      "quality_function_section_qf_tol",
      "Tolerance for the golden section search procedure determining "
      "the optimal centering parameter (in the function value space).",
      0.0, false, 1.0, true,
      0e-2,
      "The golden section search is performed for the quality function based mu "
      "oracle. (Only used if option "
      "\"mu_oracle\" is set to \"quality-function\".)");
  }
