serialize(void* dataBuffer, btSerializer* serializer) const
{
	btTypedConstraintData* tcd = (btTypedConstraintData*) dataBuffer;

	tcd->m_rbA = (btRigidBodyData*)serializer->getUniquePointer(&m_rbA);
	tcd->m_rbB = (btRigidBodyData*)serializer->getUniquePointer(&m_rbB);
	char* name = (char*) serializer->findNameForPointer(this);
	tcd->m_name = (char*)serializer->getUniquePointer(name);
	if (tcd->m_name)
	{
		serializer->serializeName(name);
	}

	tcd->m_objectType = m_objectType;
	tcd->m_needsFeedback = m_needsFeedback;
	tcd->m_userConstraintId =m_userConstraintId;
	tcd->m_userConstraintType =m_userConstraintType;

	tcd->m_appliedImpulse = float(m_appliedImpulse);
	tcd->m_dbgDrawSize = float(m_dbgDrawSize );

	tcd->m_disableCollisionsBetweenLinkedBodies = false;

	int i;
	for (i=0;i<m_rbA.getNumConstraintRefs();i++)
		if (m_rbA.getConstraintRef(i) == this)
			tcd->m_disableCollisionsBetweenLinkedBodies = true;
	for (i=0;i<m_rbB.getNumConstraintRefs();i++)
		if (m_rbB.getConstraintRef(i) == this)
			tcd->m_disableCollisionsBetweenLinkedBodies = true;

	return "btTypedConstraintData";
}
