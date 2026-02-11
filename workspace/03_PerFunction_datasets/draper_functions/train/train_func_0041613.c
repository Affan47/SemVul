object_new()
{
	object* obj= (object*)sci_malloc(sizeof(object));
	if(obj==0) return 0;

	obj->parent=0;
	FLEXARRAY_INIT(object*, obj->children);
	obj->name=0;
	obj->selector_count=0;
	obj->selector_numbers=0;
	obj->methods=0;
	obj->method_count=0;

	return obj;
}
