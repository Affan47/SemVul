Clone(FCDEntityInstance* _clone) const
{
	FCDPhysicsModelInstance* clone = NULL;
	if (_clone == NULL) _clone = clone = new FCDPhysicsModelInstance(const_cast<FCDocument*>(GetDocument()));
	else if (_clone->HasType(FCDPhysicsModelInstance::GetClassType())) clone = (FCDPhysicsModelInstance*) _clone;

	Parent::Clone(_clone);

	if (clone != NULL)
	{
		for (const FCDEntityInstance** it = instances.begin(); it != instances.end(); ++it)
		{
			FCDEntityInstance* clonedInstance = NULL;
			switch ((*it)->GetEntityType())
			{
			case FCDEntity::PHYSICS_RIGID_BODY: clonedInstance = clone->AddRigidBodyInstance(); break;
			case FCDEntity::PHYSICS_RIGID_CONSTRAINT: clonedInstance = clone->AddRigidConstraintInstance(); break;
			case FCDEntity::FORCE_FIELD: clonedInstance = clone->AddForceFieldInstance(); break;
			default: FUFail(break);
			}
			if (clonedInstance != NULL) (*it)->Clone(clonedInstance);
		}
	}
	return _clone;
}
