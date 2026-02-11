StringConversionError( bool& errorFlag, BaseGDL::Convert2Mode mode, const string& msg)
{
  if( (mode & BaseGDL::THROWIOERROR) != 0)
 {
	errorFlag = true;


  }
else
	Warning( msg);
}
