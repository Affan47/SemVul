expandlist(Tree ldef)
{
	set<string> visited;
	return expandrec(ldef, visited, nil);
}
