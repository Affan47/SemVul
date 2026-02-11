isRootDomNode( NodeImpl *node )
{
	return node && !xpathParentNode(node);
}
