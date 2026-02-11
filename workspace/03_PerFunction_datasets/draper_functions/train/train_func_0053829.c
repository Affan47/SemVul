go_component_init (GOComponent *component)
{
	component->mime_type = NULL;
	component->editable = FALSE;
	component->resizable = FALSE;
	component->priv = g_new0 (GOComponentPrivate, 1);
}
