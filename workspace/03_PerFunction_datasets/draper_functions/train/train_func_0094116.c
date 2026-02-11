media_entity_get(struct media_entity *entity)
{
	if (entity == NULL)
		return NULL;

	if (entity->parent->dev &&
	    !try_module_get(entity->parent->dev->driver->owner))
		return NULL;

	return entity;
}
