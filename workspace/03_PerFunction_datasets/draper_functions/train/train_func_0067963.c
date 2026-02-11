collectChildrenReverse( SharedPtr<DOM::StaticNodeListImpl> out,
                             DOM::NodeImpl *root )
{


	NodeImpl *n = xpathLastChild( root );
	while ( n ) {
		collectChildrenReverse( out, n );
		out->append( n );
		n = n->previousSibling();
	}
}
