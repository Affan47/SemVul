ScalarEval( int j, std::vector<double> &rStack ) const
{
  try
  {
    rStack[j] = UsefulFunctions::ComplementaryIncompleteGamma( rStack[j], rStack[j+1] );
  }
  catch (EExpressionError &e)
  {
    throw;
  }
  rStack.pop_back();
}
