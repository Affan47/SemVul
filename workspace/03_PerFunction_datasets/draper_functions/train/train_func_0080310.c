Clone(FCDEntity* _clone, bool cloneChildren) const
{
	FCDPhysicsRigidConstraint* clone = NULL;
	if (_clone == NULL) _clone = clone = new FCDPhysicsRigidConstraint(const_cast<FCDocument*>(GetDocument()), NULL);
	else if (_clone->HasType(FCDPhysicsRigidConstraint::GetClassType())) clone = (FCDPhysicsRigidConstraint*) _clone;

	Parent::Clone(_clone, cloneChildren);

	if (clone != NULL)
	{
		clone->enabled = enabled;
		clone->interpenetrate = interpenetrate;
		clone->referenceRigidBody = referenceRigidBody;
		clone->referenceNode = referenceNode;
		clone->targetRigidBody = targetRigidBody;
		clone->targetNode = targetNode;
		clone->limitsLinearMax = limitsLinearMax;
		clone->limitsLinearMin = limitsLinearMin;
		clone->limitsSCTMax = limitsSCTMax;
		clone->limitsSCTMin = limitsSCTMin;
		clone->springAngularDamping = springAngularDamping;
		clone->springAngularStiffness = springAngularStiffness;
		clone->springAngularTargetValue = springAngularTargetValue;
		clone->springLinearDamping = springLinearDamping;
		clone->springLinearStiffness = springLinearStiffness;
		clone->springLinearTargetValue = springLinearTargetValue;


		for (FCDTransformContainer::const_iterator it = transformsRef.begin(); it != transformsRef.end(); ++it)
		{
			FCDTransform* clonedTransform = clone->AddTransformRef((*it)->GetType());
			(*it)->Clone(clonedTransform);
		}
		for (FCDTransformContainer::const_iterator it = transformsTar.begin(); it != transformsTar.end(); ++it)
		{
			FCDTransform* clonedTransform = clone->AddTransformTar((*it)->GetType());
			(*it)->Clone(clonedTransform);
		}
	}
	return _clone;
}
