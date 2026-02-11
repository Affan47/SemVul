run( TestResult *result )
{
  for ( int n = 0; n < m_timesRepeat; n++ )
  {
    if ( result->shouldStop() )
        break;

    TestDecorator::run( result );
  }
}
