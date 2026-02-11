idsHashScanner (void *payload, void *data, xmlChar *name) {
	IdsIteratorInfo *priv = (IdsIteratorInfo *)data;

	if (priv->element == NULL && xmlStrEqual (name, priv->elementId))
	{
		xmlNode* parent=((xmlID *)payload)->attr->parent;
		assert(parent);
		priv->element=parent;
	}
}
