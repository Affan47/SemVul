AddCSharpHandler( vector<AbstractHandler *> & handlers,
                       xmlNode                   * node,
                       bool                        useTimestamp )
{
   string filename, enumname, cs_namespace;
   xmlChar * value;
   CSharp * p;

   value = GetMandatoryValue( node, "cs_filename" );
   if ( value == NULL ) {
      cerr << "Error: missing <cs_filename> in options file" << endl;
      return false;
   }
   stripText( value, filename );

   value = GetMandatoryValue( node, "cs_enum_name" );
   if ( value == NULL ) {
      cerr << "Error: missing <cs_enum_name> in options file" << endl;
      return false;
   }
   stripText( value, enumname );

   value = GetOptionalValue( node, "cs_namespace" );
   if ( value != NULL ) {
      stripText( value, cs_namespace );
   }

   try {
      p = new CSharp( useTimestamp, filename, cs_namespace, enumname );
   }
   catch (exception& e) {
      cerr << "C# handler exception caught opening the output file " << endl;
      throw e;
   }

   handlers.push_back(p);

   return true;
}
