RegisterOptions(SmartPtr<RegisteredOptions> roptions)
  {
    roptions->AddStringOption2(
      "linear_scaling_on_demand",
      "Flag indicating that linear scaling is only done if it seems required.",
      "yes",
      "no", "Always scale the linear system.",
      "yes", "Start using linear system scaling if solutions seem not good.",
      "This option is only important if a linear scaling method (e.g., mc19) "
      "is used.  If you choose \"no\", then the scaling factors are computed "
      "for every linear system from the start.  This can be quite expensive. "
      "Choosing \"yes\" means that the algorithm will start the scaling "
      "method only when the solutions to the linear system seem not good, and "
      "then use it until the end.");
  }
