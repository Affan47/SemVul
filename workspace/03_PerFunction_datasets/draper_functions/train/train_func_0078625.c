localGetSupportingVertex(const btVector3& vec)const
{
#ifndef __SPU__

	 btVector3	supVertex = localGetSupportingVertexWithoutMargin(vec);

	if ( getMargin()!=btScalar(0.) )
	{
		btVector3 vecnorm = vec;
		if (vecnorm .length2() < (SIMD_EPSILON*SIMD_EPSILON))
		{
			vecnorm.setValue(btScalar(-1.),btScalar(-1.),btScalar(-1.));
		}
		vecnorm.normalize();
		supVertex+= getMargin() * vecnorm;
	}
	return supVertex;

#else
	btAssert(0);
	return btVector3(0,0,0);
#endif

 }
