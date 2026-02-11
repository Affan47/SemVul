LoadExtraNodeChildren(FCDENode* fcdenode, xmlNode* customNode)
{
	bool status = true;


	for (xmlNode* k = customNode->children; k != NULL; k = k->next)
	{
		if (k->type != XML_ELEMENT_NODE) continue;

		FCDENode* node = fcdenode->AddChildNode();
		status &= (FArchiveXML::LoadSwitch(node, &node->GetObjectType(), k));
	}

	fcdenode->SetDirtyFlag();
	return status;
}
