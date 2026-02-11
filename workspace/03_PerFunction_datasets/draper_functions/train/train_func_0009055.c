plNewCapsuleShape(plReal radius, plReal height)
{


	const int numSpheres = 2;
	btVector3 positions[numSpheres] = {btVector3(0,height,0),btVector3(0,-height,0)};
	btScalar radi[numSpheres] = {radius,radius};
	void* mem = btAlignedAlloc(sizeof(btMultiSphereShape),16);
	return (plCollisionShapeHandle) new (mem)btMultiSphereShape(positions,radi,numSpheres);
}
