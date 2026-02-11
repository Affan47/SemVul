LoadPhysicsRigidConstraintInstance(FCDObject* object, xmlNode* instanceNode)
{
	if (!FArchiveXML::LoadEntityInstance(object, instanceNode)) return false;

	bool status = true;
	FCDPhysicsRigidConstraintInstance* physicsRigidConstraintInstance = (FCDPhysicsRigidConstraintInstance*)object;


	if (!IsEquivalent(instanceNode->name, DAE_INSTANCE_RIGID_CONSTRAINT_ELEMENT)
		|| physicsRigidConstraintInstance->GetModelParentInstance() == NULL
		|| physicsRigidConstraintInstance->GetModelParentInstance()->GetEntity() == NULL)
	{
		FUError::Error(FUError::ERROR_LEVEL, FUError::ERROR_UNKNOWN_ELEMENT, instanceNode->line);
		status = false;
	}

	FCDPhysicsModel* model = (FCDPhysicsModel*) physicsRigidConstraintInstance->GetModelParentInstance()->GetEntity();
	fm::string physicsRigidConstraintSid = ReadNodeProperty(instanceNode, DAE_CONSTRAINT_ATTRIBUTE);
	FCDPhysicsRigidConstraint* rigidConstraint = model->FindRigidConstraintFromSid(physicsRigidConstraintSid);
	if (!rigidConstraint)
	{
		FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_RIGID_CONSTRAINT_MISSING, instanceNode->line);
		return status;
	}
	physicsRigidConstraintInstance->SetRigidConstraint(rigidConstraint);
	physicsRigidConstraintInstance->SetDirtyFlag();
	return status;
}
