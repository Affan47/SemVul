scan( const char *fileName, istream &input )
{
	ParserDict parserDict;
	Scanner scanner( fileName, input, parserDict, 0 );
	scanner.do_scan();


	if ( ::generateGraphviz && ::graphvizGenParser != 0 )
		graphvizGenParser->pd.generateGraphviz();
}
