RegisterOptions(const SmartPtr<RegisteredOptions>& roptions)
  {
    roptions->AddLowerBoundedNumberOption(
      "nlp_scaling_max_gradient", "Maximum gradient after NLP scaling.",
      0, true, 100.0,
      "This is the gradient scaling cut-off. If the maximum"
      " gradient is above this value, then gradient based scaling"
      " will be performed. Scaling parameters are calculated to"
      " scale the maximum gradient back to this value. (This is g_max in "
      "Section 3.8 of the implementation paper.) Note: This"
      " option is only used if \"nlp_scaling_method\" is chosen as"
      " \"gradient-based\".");
    roptions->AddLowerBoundedNumberOption(
      "nlp_scaling_obj_target_gradient",
      "Target value for objective function gradient size.",
      0, false, 0.,
      "If a positive number is chosen, the scaling factor the objective "
      "function is computed so that the gradient has the max norm of the given "
      "size at the starting point.  This overrides nlp_scaling_max_gradient "
      "for the objective function.");
    roptions->AddLowerBoundedNumberOption(
      "nlp_scaling_constr_target_gradient",
      "Target value for constraint function gradient size.",
      0, false, 0.,
      "If a positive number is chosen, the scaling factor the constraint "
      "functions is computed so that the gradient has the max norm of the given "
      "size at the starting point.  This overrides nlp_scaling_max_gradient "
      "for the constraint functions.");
    roptions->AddLowerBoundedNumberOption(
      "nlp_scaling_min_value",
      "Minimum value of gradient-based scaling values.",
      0, false, 1e-8,
      "This is the lower bound for the scaling factors computed by "
      "gradient-based scaling method.  If some derivatives of some functions "
      "are huge, the scaling factors will otherwise become very small, and "
      "the (unscaled) final constraint violation, for example, might then be "
      "significant.  Note: This option is only used if \"nlp_scaling_method\" "
      "is chosen as \"gradient-based\".");
  }
