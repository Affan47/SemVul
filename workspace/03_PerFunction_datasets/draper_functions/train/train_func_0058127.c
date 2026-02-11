contains(set<Node*>&nodeSet, Node *node)
{

	if ( nodeSet.find(node) != nodeSet.end() ) return true;
	return false;
}
