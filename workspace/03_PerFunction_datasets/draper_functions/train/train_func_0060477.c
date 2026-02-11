on_stream(Stream *self, int type, iks *node)
{
	PyObject *hook;
	PyObject *doc;
	PyObject *ret;


	switch (type) {
		case IKS_NODE_NORMAL:
			if (strcmp("stream:features", iks_name(node)) == 0) {
				on_features(self, node);
			} else if (strcmp("success", iks_name(node)) == 0) {
				on_success(self, node);
			}
#if 0
		case IKS_NODE_START:
			if (!iks_is_secure(self->parser)) {
				iks_start_tls(self->parser);
				break;
			}
			if (!self->use_sasl) {
				x = iks_make_auth (, , NULL);
				iks_insert_attrib (x, "id", "auth");
				iks_send (self->parser, x);
				iks_delete (x);
			}
			break;
#endif
	hook = PyObject_GetAttrString((PyObject *) self, "on_stanza");
	if (hook) {
		doc = Document_from_iks(NULL, node);
		if (!doc) {
			Py_DECREF(hook);
			return IKS_NOMEM;
		}
		ret = PyObject_CallFunctionObjArgs(hook, doc, NULL);
		Py_DECREF(hook);

		if (ret == NULL) {
			Py_DECREF(ret);
			return IKS_HOOK;
		}
	}
	}
	if (node) iks_delete (node);
	return IKS_OK;
}
