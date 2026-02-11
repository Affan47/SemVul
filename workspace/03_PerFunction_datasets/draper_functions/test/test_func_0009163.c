operator()(object *obj)
	{
		if(type == TYPE_COUNT || obj->type() == type)
			objects.push_back(tag_dynamic(obj));
	}
