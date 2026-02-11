gc_web_service_build_xpath_context (GcWebService *self)
{
	xmlDocPtr doc;
	xmlChar *tmp;


	if (self->xpath_ctx) {
		return TRUE;
	}


	tmp = xmlStrndup(self->response, self->response_length);
	doc = xmlParseDoc (tmp);
	if (!doc) {

		g_free (tmp);
		return FALSE;
	}
	xmlFree (tmp);

	self->xpath_ctx = xmlXPathNewContext(doc);
	if (!self->xpath_ctx) {

		return FALSE;
	}
	gc_web_service_register_namespaces (self);
	return TRUE;
}
