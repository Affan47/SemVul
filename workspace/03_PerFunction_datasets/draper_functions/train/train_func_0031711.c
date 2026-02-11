ContainsPoint(const Point& p) const
{


	Point RelPoint = p - mCenter;


	float f = mRot.m[0][0] * RelPoint.x + mRot.m[0][1] * RelPoint.y + mRot.m[0][2] * RelPoint.z;
	if(f >= mExtents.x || f <= -mExtents.x) return false;

	f = mRot.m[1][0] * RelPoint.x + mRot.m[1][1] * RelPoint.y + mRot.m[1][2] * RelPoint.z;
	if(f >= mExtents.y || f <= -mExtents.y) return false;

	f = mRot.m[2][0] * RelPoint.x + mRot.m[2][1] * RelPoint.y + mRot.m[2][2] * RelPoint.z;
	if(f >= mExtents.z || f <= -mExtents.z) return false;
	return true;
}
