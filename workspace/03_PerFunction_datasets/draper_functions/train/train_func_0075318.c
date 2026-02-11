endCodeGen( int endLine )
{
	if ( ! inhibitLineDirectives ) {

		*outStream << "#line " << endLine << " \"" << fileName << "\"\n";
	}
}
