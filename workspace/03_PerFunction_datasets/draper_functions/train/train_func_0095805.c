addError( ErrorXML & error,
                       bool       lastError ) throw( MissingException )
{
   bool firstpara = true;
   string tmp;
   string & errNumber = error.GetErrNumber();
   string & errName   = error.GetErrName();
   const char * paragraph;

   paragraph = error.GetDocuParagraph();
   while ( paragraph != NULL ) {
      stripText( paragraph, tmp );
      if ( tmp.empty() ) throw new MissingException( "<errordoc>" );

      if ( firstpara ) firstpara = false;
      else {
         outStream << indent << "    //" << endl;
      }
      if ( my_namespace.length() == 0 ) {
         formatText( outStream, tmp, "    // ", ERRP_LINE_LENGTH );
      }
      else {
         formatText( outStream, tmp, "        // ", ERRP_LINE_LENGTH );
      }

      paragraph = error.GetDocuParagraph();
   }

   outStream << indent << "    " << errName << " = " << errNumber;
   if (! lastError) outStream << "," << endl << endl;
}
