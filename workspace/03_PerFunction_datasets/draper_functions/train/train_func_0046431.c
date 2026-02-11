displayActionError( const ActionResult& result, const ASCString& additionalInfo  )
{
   ASCString s = getmessage(result.getCode());
   s += "\n" + result.getMessage();
   if ( !additionalInfo.empty() )
      s += "\n" + additionalInfo;

   errorMessage( s );
}
