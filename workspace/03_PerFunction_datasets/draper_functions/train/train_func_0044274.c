GetVisualSceneInstance() const
{
	if (visualSceneRoot == NULL) return NULL;
	const FCDEntity* entity = visualSceneRoot->GetEntity();
	if (entity != NULL && entity->HasType(FCDSceneNode::GetClassType())) return (const FCDSceneNode*) entity;
	else return NULL;
}
