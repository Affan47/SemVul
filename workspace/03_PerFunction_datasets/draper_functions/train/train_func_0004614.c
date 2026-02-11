SaveFile( FILE* fp )
{
	XMLPrinter stream( fp );
	Print( &stream );
	return errorID;
}
