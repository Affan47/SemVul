update3DObject(mrpt::aligned_containers<mrpt::poses::CPose3D>::vector_t *out_all_poses ) const
{
	ASSERTMSG_((m_links.size()+1)==m_last_gl_objects.size(), "The kinematic chain has changed since the last call to getAs3DObject()")

	const size_t N=m_links.size();


	mrpt::aligned_containers<mrpt::poses::CPose3D>::vector_t all_poses;
	recomputeAllPoses( all_poses );

	for (size_t i=0;i<=N;i++)
	{
		mrpt::opengl::CSetOfObjectsPtr gl_objs = mrpt::opengl::CSetOfObjectsPtr(m_last_gl_objects[i]);
		gl_objs->setPose( all_poses[i] );

		if (i<N)
		{
			mrpt::opengl::CCylinderPtr glCyl = mrpt::opengl::CCylinderPtr( gl_objs->getByName("cyl.d") );
			const double d = m_links[i].d;
			glCyl->setHeight( d );
		}

		if (i>0)
		{
			mrpt::opengl::CCylinderPtr glCyl2 = mrpt::opengl::CCylinderPtr( gl_objs->getByName("cyl.a") );
			const double a = m_links[i-1].a;

			glCyl2->setHeight( -a );
		}
	}

	if (out_all_poses)
		out_all_poses->swap(all_poses);
}
