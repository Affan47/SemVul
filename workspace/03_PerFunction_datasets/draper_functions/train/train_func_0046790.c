insertAnotherMap(
	const CPointsMap	*otherMap,
	const CPose3D		&otherPose)
{
	const size_t N_this = size();
	const size_t N_other = otherMap->size();


	this->resize( N_this + N_other );

	mrpt::math::TPoint3Df pt;
	size_t src,dst;
	for (src=0, dst=N_this; src<N_other; src++, dst++)
	{

		otherMap->getPointFast(src,pt.x,pt.y,pt.z);


		double gx,gy,gz;
		otherPose.composePoint(pt.x,pt.y,pt.z,  gx,gy,gz);


		this->setPointFast(dst,gx,gy,gz);
	}


	addFrom_classSpecific(*otherMap, N_this);

	mark_as_modified();
}
