printFailureDetail( TestFailure *failure )
{
  printFailureLocation( failure->sourceLine() );
  printFailureType( failure );
  printFailedTestName( failure );
  printFailureMessage( failure );
}
