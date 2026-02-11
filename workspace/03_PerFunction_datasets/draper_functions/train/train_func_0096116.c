PSolve_RContacts(btSoftBody* psb,btScalar kst,btScalar ti)
{
	const btScalar	dt=psb->m_sst.sdt;
	const btScalar	mrg=psb->getCollisionShape()->getMargin();
	for(int i=0,ni=psb->m_rcontacts.size();i<ni;++i)
	{
		const RContact&		c=psb->m_rcontacts[i];
		const sCti&			cti=c.m_cti;
		btRigidBody* tmpRigid = btRigidBody::upcast(cti.m_colObj);

		const btVector3		va=tmpRigid ? tmpRigid->getVelocityInLocalPoint(c.m_c1)*dt : btVector3(0,0,0);
		const btVector3		vb=c.m_node->m_x-c.m_node->m_q;
		const btVector3		vr=vb-va;
		const btScalar		dn=btDot(vr,cti.m_normal);
		if(dn<=SIMD_EPSILON)
		{
			const btScalar		dp=btMin(btDot(c.m_node->m_x,cti.m_normal)+cti.m_offset,mrg);
			const btVector3		fv=vr-cti.m_normal*dn;
			const btVector3		impulse=c.m_c0*((vr-fv*c.m_c3+cti.m_normal*(dp*c.m_c4))*kst);
			c.m_node->m_x-=impulse*c.m_c2;
			if (tmpRigid)
				tmpRigid->applyImpulse(impulse,c.m_c1);
		}
	}
}
