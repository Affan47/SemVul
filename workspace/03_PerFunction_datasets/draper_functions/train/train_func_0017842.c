contains(const TPoint3D &point) const	{
	TPoint3D pMin,pMax;
	getPrismBounds(*this,pMin,pMax);
	if (point.x+geometryEpsilon<pMin.x||point.y+geometryEpsilon<pMin.y||point.z+geometryEpsilon<pMin.z||point.x>pMax.x+geometryEpsilon||point.y>pMax.y+geometryEpsilon||point.z>pMax.z+geometryEpsilon) return false;
	TPlane plane;
	if (!getPlane(plane)) throw std::logic_error("Polygon does not conform a plane");
	TPolygon3D projectedPoly;
	TPoint3D projectedPoint;
	mrpt::poses::CPose3D pose;

	plane.getAsPose3D(pose);
	pose=mrpt::poses::CPose3D(0,0,0,0,0,0)-pose;
	project3D(point,pose,projectedPoint);
	if (abs(projectedPoint.z)>=geometryEpsilon) return false;
	project3D(*this,pose,projectedPoly);
	return TPolygon2D(projectedPoly).contains(TPoint2D(projectedPoint));
}
