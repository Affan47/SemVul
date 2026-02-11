vc_destroyValidityChecker(VC vc)
{
  try{
  CVC3::ValidityChecker* cvc = (CVC3::ValidityChecker*) vc;
  delete cvc;
  } catch (CVC3::Exception ex){
    signal_error("vc_destroyVelidityChecker",error_int,ex);
  }
}
