VerifyVectorType(MVT VT, EVT ArgVT) {
  if (ArgVT.isVector() && !VT.isVector())
    report_fatal_error("Unsupported vector argument or return type");
}
