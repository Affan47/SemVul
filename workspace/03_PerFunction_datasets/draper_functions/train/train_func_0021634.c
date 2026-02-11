deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	Center = in->getAttributeAsVector3d("Center");
	Radius = in->getAttributeAsFloat("Radius");
	Speed = in->getAttributeAsFloat("Speed");
	Direction = in->getAttributeAsVector3d("Direction");
	StartTime = 0;

	if (Direction.equals(core::vector3df(0,0,0)))
		Direction.set(0,1,0);
	else
		Direction.normalize();

	RadiusEllipsoid = in->getAttributeAsFloat("RadiusEllipsoid");
	init();
}
