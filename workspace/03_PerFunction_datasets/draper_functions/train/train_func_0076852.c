doinit() {
  for(int ix=1;ix<7;++ix) {
    addToList(-ix,ix,21,39);
  }
  FFVTVertex::doinit();
  tcHwRSPtr hwRS=dynamic_ptr_cast<tcHwRSPtr>(generator()->standardModel());
  if(!hwRS) throw Exception()
	      << "Must have RSModel in RSModelFFGGRVertex::doinit()"
	      << Exception::runerror;
  kappa_ = 2./hwRS->lambda_pi();
}
