GetErrMessage( const char * nodeMsg,
                                string     & message ) throw( MissingException )
{
   string errMessage, tmp;

   stripText( nodeMsg, tmp );
   if ( tmp.empty() ) throw new MissingException( "<errormsg>" );
   stripPercent( tmp, errMessage );
   tmp.clear();


   hasEscapeSequence( errMessage );

   if ( hasUnescapedQuotes(errMessage) ) {
      if ( ! allowQuotes ) {
         cerr << "Quotes are not allowed, string: " << errMessage << endl;
         exit(1);
      }
      escapeUnescapedQuotes( errMessage, tmp );
      message = tmp;
   }
   else {
      message = errMessage;
   }
}
