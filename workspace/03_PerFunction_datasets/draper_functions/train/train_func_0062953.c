DebugParseTree(RefAST ast)
{
	std::ofstream strmOut;
	strmOut.open("dbg_parsetree.txt");
	if (strmOut.fail())
	{
		g_errorList.AddError(6106, NULL,
			"Error in writing to file ",
			"dbg_parsetree.txt");
		return;
	}

	strmOut << "PARSE TREE\n\n";

	ast->Trace(strmOut, 0, 0);

	strmOut.close();
}
