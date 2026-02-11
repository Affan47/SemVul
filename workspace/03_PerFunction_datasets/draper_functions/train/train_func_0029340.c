posePDF2opengl(const CPointPDF &o)
{
	CSetOfObjectsPtr outObj = CSetOfObjects::Create();

	if (IS_CLASS(&o,CPointPDFSOG))
	{
		const CPointPDFSOG *p = static_cast<const CPointPDFSOG*>(&o);


		for (CPointPDFSOG::CListGaussianModes::const_iterator it = p->begin(); it!= p->end();++it)
		{
			opengl::CEllipsoidPtr obj = opengl::CEllipsoid::Create();

			obj->setPose( it->val.mean);
			obj->setCovMatrix(it->val.cov,  it->val.cov(2,2)==0  ?  2:3);

			obj->setQuantiles(3);
			obj->enableDrawSolid3D(false);
			obj->setColor(POINT_COLOR);

			outObj->insert( obj );
		}
	}
	else if (IS_CLASS(&o, CPointPDFGaussian))
	{
		const CPointPDFGaussian *p = static_cast<const CPointPDFGaussian*>(&o);

		CEllipsoidPtr obj = CEllipsoid::Create();
		obj->setLocation(p->mean);
		obj->setCovMatrix(p->cov,  p->cov(2,2)==0  ?  2:3);
		obj->setColor(POINT_COLOR);
		obj->setQuantiles(3);
		obj->enableDrawSolid3D(false);
		outObj->insert( obj );
	}
	else if (IS_CLASS(&o, CPointPDFParticles))
	{
		const CPointPDFParticles *p = static_cast<const CPointPDFParticles*>(&o);

		mrpt::opengl::CPointCloudPtr obj = mrpt::opengl::CPointCloud::Create();
		const size_t N=p->size();

		obj->resize(N);
		obj->setColor(POINT_COLOR);
		for (size_t i=0;i<N;i++)
			obj->setPoint(
				i,
				p->m_particles[i].d->x,
				p->m_particles[i].d->y,
				p->m_particles[i].d->z );
		outObj->insert( obj );
	}

	return outObj;
}
