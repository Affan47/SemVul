contains(const TPoint3D &point) const	{
	double dx=point.x-pBase.x;
	double dy=point.y-pBase.y;
	double dz=point.z-pBase.z;
	if (abs(dx)<geometryEpsilon&&abs(dy)<geometryEpsilon&&abs(dz)<geometryEpsilon) return true;


	return (abs(dx*director[1]-dy*director[0])<geometryEpsilon)&&(abs(dx*director[2]-dz*director[0])<geometryEpsilon)&&(abs(dy*director[2]-dz*director[1])<geometryEpsilon);
}
