handleError( StkError::Type type )
{
  handleError( errorString_.str(), type );
  errorString_.str( std::string() );
}
