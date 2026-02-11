CreateAnalyticalGeometry(FCDPhysicsAnalyticalGeometry::GeomType type)
{
	SAFE_RELEASE(geometry);
	analGeom = FCDPASFactory::CreatePAS(GetDocument(), type);
	SetNewChildFlag();
	return analGeom;
}
