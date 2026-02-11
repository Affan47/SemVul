EvaluateAndDisplay(Expression *pExpr) {
  try {
    Value * pValue = pExpr->evaluate();
    GetUserInterface().DisplayMessage("%s\n", pValue->toString().c_str());
  }
  catch(Error *pMessage)  {
    GetUserInterface().DisplayMessage("%s\n", pMessage->toString().c_str());
  }
}
