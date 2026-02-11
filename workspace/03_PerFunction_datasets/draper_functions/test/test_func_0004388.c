vc_setTriggers(VC vc, Expr e, int numTrigs, Expr* triggers)
{
  try{
  CVC3::ValidityChecker* cvc = (CVC3::ValidityChecker*) vc;
  vector<vector<CVC3::Expr> >cvcTriggers;
  for (int i = 0; i < numTrigs; ++i) {
    vector<CVC3::Expr> curTrig;
    CVC3::Expr trigExpr = fromExpr(triggers[i]);
    if(trigExpr.isRawList()){
      for(int j = 0 ; j < trigExpr.arity(); j++){
       curTrig.push_back(trigExpr[j]);
      }
    }
    else{
      curTrig.push_back(trigExpr);
    }
    cvcTriggers.push_back(curTrig);
  }

  cvc->setTriggers(fromExpr(e), cvcTriggers);
  }catch(CVC3::Exception ex){
    signal_error("vc_setTriggers",error_int,ex);
  }
}
