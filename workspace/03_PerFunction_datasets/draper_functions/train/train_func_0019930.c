deleteBeautifierVectors()
{
	beautifierFileType = 9;
	delete headers;
	delete nonParenHeaders;
	delete preBlockStatements;
	delete preCommandHeaders;
	delete assignmentOperators;
	delete nonAssignmentOperators;
	delete indentableHeaders;
}
