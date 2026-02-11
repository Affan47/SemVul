MoveItems (Object* obj, double dx, double dy)
{
	Object* pObject;
	gccv::ItemClient *client = dynamic_cast <gccv::ItemClient *> (obj);
	gccv::Item *item = (client)? client->GetItem (): NULL;
	if (item && item->GetParent ()->GetParent () == NULL)
		item->Move (dx, dy);
	std::map<std::string, Object*>::iterator i;
	pObject = obj->GetFirstChild (i);
	while (pObject) {
		MoveItems (pObject, dx, dy);
		pObject = obj->GetNextChild (i);
	}
}
