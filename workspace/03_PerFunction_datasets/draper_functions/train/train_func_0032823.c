go_doc_set_pristine (GODoc *doc, gboolean pristine)
{
	g_return_if_fail (GO_IS_DOC (doc));

	pristine = !!pristine;
	if (pristine == doc->pristine)
		return;

	doc->pristine = pristine;
	g_object_notify (G_OBJECT (doc), "pristine");
}
