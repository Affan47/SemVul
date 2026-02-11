Clone(FCDEntity* _clone, bool cloneChildren) const
{
	FCDPhysicsRigidBody* clone = NULL;
	if (_clone == NULL) _clone = clone = new FCDPhysicsRigidBody(const_cast<FCDocument*>(GetDocument()));
	else if (_clone->HasType(FCDPhysicsRigidBody::GetClassType())) clone = (FCDPhysicsRigidBody*) _clone;

	Parent::Clone(_clone, cloneChildren);

	if (clone != NULL)
	{
		clone->GetParameters()->CopyFrom(*parameters);
	}
	return _clone;
}
