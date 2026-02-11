deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{


	core::vector3df b = in->getAttributeAsVector3d("Box");

	if (b.X <= 0)
		b.X = 1.0f;
	if (b.Y <= 0)
		b.Y = 1.0f;
	if (b.Z <= 0)
		b.Z = 1.0f;

	Box.MinEdge.X = -b.X;
	Box.MinEdge.Y = -b.Y;
	Box.MinEdge.Z = -b.Z;
	Box.MaxEdge.X = b.X;
	Box.MaxEdge.Y = b.Y;
	Box.MaxEdge.Z = b.Z;

	Direction = in->getAttributeAsVector3d("Direction");
	if (Direction.getLength() == 0)
		Direction.set(0,0.01f,0);

	MinStartSize.Width = in->getAttributeAsFloat("MinStartSizeWidth");
	MinStartSize.Height = in->getAttributeAsFloat("MinStartSizeHeight");
	MaxStartSize.Width = in->getAttributeAsFloat("MaxStartSizeWidth");
	MaxStartSize.Height = in->getAttributeAsFloat("MaxStartSizeHeight");

	MinParticlesPerSecond = in->getAttributeAsInt("MinParticlesPerSecond");
	MaxParticlesPerSecond = in->getAttributeAsInt("MaxParticlesPerSecond");

	MinParticlesPerSecond = core::max_(1u, MinParticlesPerSecond);
	MaxParticlesPerSecond = core::max_(MaxParticlesPerSecond, 1u);
	MaxParticlesPerSecond = core::min_(MaxParticlesPerSecond, 200u);
	MinParticlesPerSecond = core::min_(MinParticlesPerSecond, MaxParticlesPerSecond);

	MinStartColor = in->getAttributeAsColor("MinStartColor");
	MaxStartColor = in->getAttributeAsColor("MaxStartColor");
	MinLifeTime = in->getAttributeAsInt("MinLifeTime");
	MaxLifeTime = in->getAttributeAsInt("MaxLifeTime");
	MaxAngleDegrees = in->getAttributeAsInt("MaxAngleDegrees");

	MinLifeTime = core::max_(0u, MinLifeTime);
	MaxLifeTime = core::max_(MaxLifeTime, MinLifeTime);
	MinLifeTime = core::min_(MinLifeTime, MaxLifeTime);

}
