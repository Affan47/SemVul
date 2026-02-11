slerp(
	const CPose3D  & p0,
	const CPose3D  & p1,
	const double     t,
	CPose3D        & p)
{
	CQuaternionDouble q0,q1,q;
	p0.getAsQuaternion(q0);
	p1.getAsQuaternion(q1);

	mrpt::math::slerp(q0,q1,t, q);

	p = CPose3D(
		q,
		(1-t)*p0.x()+t*p1.x(),
		(1-t)*p0.y()+t*p1.y(),
		(1-t)*p0.z()+t*p1.z() );
}
