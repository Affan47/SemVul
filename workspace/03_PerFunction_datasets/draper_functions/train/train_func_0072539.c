initialize(std::vector< GeometryNode* >& nds, std::vector< GeometryEdge* >& eds)
{
	initialized = true;

	nodes = nds;

	int i;
	int len = nodes.size();

	for( i = 0; i < len; ++i )
	{
		border.push_back( nodes[i] );
	}

	makeWorld();

	len = border.size();
	int *indirect = new int[len];
	for( i = 0; i < len; ++i)
	{
		indirect[i] = i;
	}
	std::random_shuffle(indirect, indirect + len);

	for( i = 0; i < len; ++i)
	{
		int ind = indirect[i];
		Vertex *vtx = root->firstAcceptableFound( border[ind]->x, border[ind]->y);
		addSite( vtx, border[ind], true );
		GeometryNode *nd = static_cast<GeometryNode *>( border[ind] );
		recycle();
	}

	delete [] indirect;


	std::list< Vertex* >::iterator vxIt;
	for( vxIt = allVertices.begin(); vxIt != allVertices.end(); ++vxIt )
	{
		BGVertex *vtx = static_cast< BGVertex * >(*vxIt);
		if( !(vtx->isDeleted()) )
		{
			vtx->initInterpolation( );
		}
	}
	dump();
}
