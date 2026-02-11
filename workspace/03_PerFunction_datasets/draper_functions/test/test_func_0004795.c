mono_image_invoke_unload_hook (MonoImage *image)
{
	GSList *l;
	ImageUnloadHook *hook;

	for (l = image_unload_hooks; l; l = l->next) {
		hook = l->data;

		hook->func (image, hook->user_data);
	}
}
