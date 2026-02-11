RemoveTag(WokXMLTag *tag)
{
	std::list <WokXMLTag *>::iterator tagiter;
	tagiter = find(tags.begin(), tags.end(), tag);
	if (tagiter != tags.end())
	{
		tags.erase(tagiter);
	}

	std::list <WokXMLObject *>::iterator objiter;
	objiter = find(object_list.begin(), object_list.end(), static_cast<WokXMLObject*>(tag));
	if (objiter != object_list.end())
	{
		object_list.erase(objiter);
	}

	tagiter = find(object_reference[tag->GetName()].begin(), object_reference[tag->GetName()].end(), tag);
	if (tagiter != object_reference[tag->GetName()].end())
	{
		object_reference[tag->GetName()].erase(tagiter);
	}

	tagiter = find(namespace_list[tag->GetAttr("xmlns")].begin(), namespace_list[tag->GetAttr("xmlns")].end(), tag);
	if ( tagiter != namespace_list[tag->GetAttr("xmlns")].end() )
		namespace_list[tag->GetAttr("xmlns")].erase(tagiter);

	tagiter = find(namespace_reference[tag->GetAttr("name")][tag->GetAttr("xmlns")].begin(), namespace_reference[tag->GetAttr("name")][tag->GetAttr("xmlns")].end(), tag);
	if ( tagiter != namespace_reference[tag->GetAttr("name")][tag->GetAttr("xmlns")].end() )
		namespace_reference[tag->GetAttr("name")][tag->GetAttr("xmlns")].erase(tagiter);

	tag->parant = NULL;
}
