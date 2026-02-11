setAnimatedMeshSceneNode( IAnimatedMeshSceneNode* node )
{
	Node = node;
	AnimatedMesh = 0;
	BaseMesh = 0;
	TotalVertices = 0;
	VertexPerMeshBufferList.clear();
	if ( !node )
	{
		return;
	}

	AnimatedMesh = node->getMesh();
	BaseMesh = AnimatedMesh->getMesh(0);

	MBCount = BaseMesh->getMeshBufferCount();
	VertexPerMeshBufferList.reallocate(MBCount);
	for( u32 i = 0; i < MBCount; ++i )
	{
		VertexPerMeshBufferList.push_back( BaseMesh->getMeshBuffer(i)->getVertexCount() );
		TotalVertices += BaseMesh->getMeshBuffer(i)->getVertexCount();
	}
}
