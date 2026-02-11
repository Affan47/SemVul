doinit() {
  addToList(23,23,39);
  addToList(22,22,39);
  addToList(24,-24,39);
  addToList(21,21,39);
  VVTVertex::doinit();
  tcHwRSPtr hwRS=dynamic_ptr_cast<tcHwRSPtr>(generator()->standardModel());
  if(!hwRS)
    throw Exception() << "Must be RSModel in RSModelVVGRVertex::doinit()"
		      << Exception::runerror;
  kappa_=2./hwRS->lambda_pi();
}
