CalculateWorldTransform() const
{
	const FCDSceneNode* parent = GetParent();
	if (parent != NULL)
	{


		return parent->CalculateWorldTransform() * CalculateLocalTransform();
	}
	else
	{
		return CalculateLocalTransform();
	}
}
