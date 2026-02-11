addSphereSceneNode(f32 radius, s32 polyCount,
		ISceneNode* parent, s32 id, const core::vector3df& position,
		const core::vector3df& rotation, const core::vector3df& scale)
{
	if (!parent)
		parent = this;

	IMeshSceneNode* node = new CSphereSceneNode(radius, polyCount, polyCount, parent, this, id, position, rotation, scale);
	node->drop();

	return node;
}
