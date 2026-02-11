external_scroller_content_get(void *data __UNUSED__,
		const Evas_Object *obj, const char *content)
{
	if (!strcmp(content, "content"))
		return elm_object_content_get(obj);

	ERR("unknown content '%s'", content);
	return NULL;
}
