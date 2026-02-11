RegisterOptions(SmartPtr<RegisteredOptions> roptions)
  {
    roptions->SetRegisteringCategory("NLP");
    roptions->AddNumberOption(
      "nlp_lower_bound_inf",
      "any bound less or equal this value will be considered -inf (i.e. not lower bounded).",
      -1e19);
    roptions->AddNumberOption(
      "nlp_upper_bound_inf",
      "any bound greater or this value will be considered +inf (i.e. not upper bounded).",
      1e19);
    roptions->AddStringOption3(
      "fixed_variable_treatment",
      "Determines how fixed variables should be handled.",
      "make_parameter",
      "make_parameter", "Remove fixed variable from optimization variables",
      "make_constraint", "Add equality constraints fixing variables",
      "relax_bounds", "Relax fixing bound constraints",
      "The main difference between those options is that the starting "
      "point in the \"make_constraint\" case still has the fixed variables at "
      "their given values, whereas in the case \"make_parameter\" the "
      "functions are always evaluated with the fixed values for those "
      "variables.  Also, for \"relax_bounds\", the fixing bound "
      "constraints are relaxed (according to\" bound_relax_factor\"). For "
      "both \"make_constraints\" and \"relax_bounds\", bound multipliers are "
      "computed for the fixed variables.");
    roptions->AddStringOption4(
      "dependency_detector",
      "Indicates which linear solver should be used to detect linearly dependent equality constraints.",
      "none",
      "none", "don't check; no extra work at beginning",
      "mumps", "use MUMPS",
      "wsmp", "use WSMP",
      "ma28", "use MA28",
      "The default and available choices depend on how Ipopt has been "
      "compiled.  This is experimental and does not work well.");
    roptions->AddStringOption2(
      "dependency_detection_with_rhs",
      "Indicates if the right hand sides of the constraints should be considered during dependency detection",
      "no",
      "no", "only look at gradients",
      "yes", "also consider right hand side",
      "");
    roptions->AddLowerBoundedIntegerOption(
      "num_linear_variables",
      "Number of linear variables",
      0, 0,
      "When the Hessian is approximated, it is assumed that the first "
      "num_linear_variables variables are linear.  The Hessian is then not "
      "approximated in this space.  If the get_number_of_nonlinear_variables "
      "method in the TNLP is implemented, this option is ignored.");

    roptions->SetRegisteringCategory("Derivative Checker");
    roptions->AddStringOption4(
      "derivative_test",
      "Enable derivative checker",
      "none",
      "none", "do not perform derivative test",
      "first-order", "perform test of first derivatives at starting point",
      "second-order", "perform test of first and second derivatives at starting point",
      "only-second-order", "perform test of second derivatives at starting point",
      "If this option is enabled, a (slow!) derivative test will be performed "
      "before the optimization.  The test is performed at the user provided "
      "starting point and marks derivative values that seem suspicious");
    roptions->AddLowerBoundedIntegerOption(
      "derivative_test_first_index",
      "Index of first quantity to be checked by derivative checker",
      -2, -2,
      "If this is set to -2, then all derivatives are checked.  Otherwise, "
      "for the first derivative test it specifies the first variable for "
      "which the test is done (counting starts at 0).  For second "
      "derivatives, it specifies the first constraint for which the test is "
      "done; counting of constraint indices starts at 0, and -1 refers to the "
      "objective function Hessian.");
    roptions->AddLowerBoundedNumberOption(
      "derivative_test_perturbation",
      "Size of the finite difference perturbation in derivative test.",
      0., true,
      1e-8,
      "This determines the relative perturbation of the variable entries.");
    roptions->AddLowerBoundedNumberOption(
      "derivative_test_tol",
      "Threshold for indicating wrong derivative.",
      0., true,
      1e-4,
      "If the relative deviation of the estimated derivative from the given "
      "one is larger than this value, the corresponding derivative is marked "
      "as wrong.");
    roptions->AddStringOption2(
      "derivative_test_print_all",
      "Indicates whether information for all estimated derivatives should be printed.",
      "no",
      "no", "Print only suspect derivatives",
      "yes", "Print all derivatives",
      "Determines verbosity of derivative checker.");
    roptions->AddStringOption2(
      "jacobian_approximation",
      "Specifies technique to compute constraint Jacobian",
      "exact",
      "exact", "user-provided derivatives",
      "finite-difference-values", "user-provided structure, values by finite differences"
    );
    roptions->AddLowerBoundedNumberOption(
      "findiff_perturbation",
      "Size of the finite difference perturbation for derivative approximation.",
      0., true,
      1e-7,
      "This determines the relative perturbation of the variable entries.");
    roptions->AddLowerBoundedNumberOption(
      "point_perturbation_radius",
      "Maximal perturbation of an evaluation point.",
      0., false,
      10.,
      "If a random perturbation of a points is required, this number "
      "indicates the maximal perturbation.  This is for example used when "
      "determining the center point at which the finite difference derivative "
      "test is executed.");
  }
