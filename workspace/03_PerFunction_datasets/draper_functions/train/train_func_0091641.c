clone(ISceneNode* newParent, ISceneManager* newManager)
{
	if (!newParent)
		newParent = Parent;
	if (!newManager)
		newManager = SceneManager;

	CCameraSceneNode* nb = new CCameraSceneNode(newParent,
		newManager, ID, RelativeTranslation, Target);

	nb->cloneMembers(this, newManager);

	if ( newParent )
		nb->drop();
	return nb;
}
