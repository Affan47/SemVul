obj_get_name(struct _state *s, reg_t pos)
{
	object_t *obj = obj_get(s, pos);

	if (!obj)
		return "<no such object>";

	return
		(const char*)(obj->base + obj->variables[SCRIPT_NAME_SELECTOR].offset);
}
