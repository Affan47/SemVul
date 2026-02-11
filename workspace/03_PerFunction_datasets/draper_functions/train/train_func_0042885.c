posePDF2opengl(const CPose3DPDF &o)
{
	CSetOfObjectsPtr outObj = CSetOfObjects::Create();

	if (IS_CLASS(&o,CPose3DPDFSOG))
	{
		const CPose3DPDFSOG *p = static_cast<const CPose3DPDFSOG*>(&o);


		for (CPose3DPDFSOG::const_iterator it = p->begin(); it!= p->end();++it)
		{
			opengl::CEllipsoidPtr obj = opengl::CEllipsoid::Create();

			obj->setPose( it->val.mean);
			obj->setCovMatrix(CMatrixDouble(it->val.cov),  it->val.cov(2,2)==0  ?  2:3);

			obj->setQuantiles(3);
			obj->enableDrawSolid3D(false);
			obj->setColor(POSE_COLOR);

			outObj->insert( obj );

			opengl::CSetOfObjectsPtr axes = opengl::stock_objects::CornerXYZ();
			axes->setPose(it->val.mean);
			axes->setScale(POSE_AXIS_SCALE);
			outObj->insert(axes);
		}
	}
	else
	if (IS_CLASS(&o,CPose3DPDFGaussian))
	{
		const CPose3DPDFGaussian *p = static_cast<const CPose3DPDFGaussian*>(&o);

		opengl::CEllipsoidPtr obj = opengl::CEllipsoid::Create();

		obj->setPose( p->mean);
		obj->setCovMatrix(CMatrixDouble(p->cov),  p->cov(2,2)==0  ?  2:3);

		obj->setQuantiles(3);
		obj->enableDrawSolid3D(false);
		obj->setColor(POSE_COLOR);

		outObj->insert( obj );

		opengl::CSetOfObjectsPtr axes = opengl::stock_objects::CornerXYZ();
		axes->setPose(p->mean);
		axes->setScale(POSE_AXIS_SCALE);
		outObj->insert(axes);
	}
	else
	if (IS_CLASS(&o,CPose3DPDFParticles))
	{
		const CPose3DPDFParticles *p = static_cast<const CPose3DPDFParticles*>(&o);

		for (size_t i=0;i<p->size();i++)
		{
			opengl::CSetOfObjectsPtr axes = opengl::stock_objects::CornerXYZSimple(POSE_AXIS_SCALE);
			axes->setPose(*p->m_particles[i].d);
			outObj->insert(axes);
		}

	}

	return outObj;
}
