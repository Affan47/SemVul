getPreviousPoseWithMinDistance(  const mrpt::system::TTimeStamp &t, double distance, CPose3D &out_pose )
{
	if( m_path.size() == 0 || distance <=0 )
		return false;

	CPose3D			myPose;


	iterator  it = m_path.find(t);
	if( it != m_path.end() && it != m_path.begin() )
		myPose = it->second;
	else
		return false;


	double d = 0.0;
	do
	{
		--it;
		d = myPose.distance2DTo( it->second.x(), it->second.y());
	} while( d < distance && it != m_path.begin() );

	if( d >= distance )
	{
		out_pose = it->second;
		return true;
	}
	else
		return false;
}
