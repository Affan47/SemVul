ScalarEval( int j, std::vector<double> &rStack ) const
{
  try
  {
    rStack[j] = UsefulFunctions::IncompleteBeta( rStack[j], rStack[j+1], rStack[j+2] );
  }
  catch (EExpressionError &e)
  {
    throw;
  }
  rStack.pop_back();
  rStack.pop_back();
}
