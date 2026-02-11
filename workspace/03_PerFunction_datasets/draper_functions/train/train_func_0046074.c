createOctreeTriangleSelector(IMesh* mesh,
																ISceneNode* node,
																s32 minimalPolysPerNode)
{
	if (!mesh)
		return 0;

	return new COctreeTriangleSelector(mesh, node, minimalPolysPerNode);
}
