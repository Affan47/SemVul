getCurrentEstimate(
	TPose2D &pose, float &v, float &w,
	TTimeStamp tim_query
	) const
{
	if (m_last_odo_time==INVALID_TIMESTAMP || m_last_loc_time==INVALID_TIMESTAMP )
		return false;

	const double dTimeLoc = timeDifference(m_last_loc_time,tim_query);
	if (dTimeLoc>params.max_localiz_age)
		return false;


	v = m_robot_v;
	w = m_robot_w;


	const TPose2D p = TPose2D(  CPose2D(m_last_loc) + ( CPose2D(m_last_odo) - CPose2D(m_loc_odo_ref) ) );


	const double dTimeOdo = timeDifference(m_last_odo_time,tim_query);
	if (dTimeOdo >params.max_odometry_age)
		return false;

	extrapolateRobotPose(
		p,m_robot_v,m_robot_w,
		dTimeOdo,
		pose);

	return true;
}
