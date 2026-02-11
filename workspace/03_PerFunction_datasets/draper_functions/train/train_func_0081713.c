localGetSupportingVertex(const btVector3& vec) const
{
	btVector3 supportVertex;

	btTransform ident;
	ident.setIdentity();

	SupportVertexCallback supportCallback(vec,ident);

	btVector3 aabbMax(btScalar(BT_LARGE_FLOAT),btScalar(BT_LARGE_FLOAT),btScalar(BT_LARGE_FLOAT));

	processAllTriangles(&supportCallback,-aabbMax,aabbMax);

	supportVertex = supportCallback.GetSupportVertexLocal();

	return supportVertex;
}
