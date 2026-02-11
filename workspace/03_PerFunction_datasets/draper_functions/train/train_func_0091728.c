mono_class_alloc_ext (MonoClass *klass)
{
	MonoClassExt *ext;

	if (klass->ext)
		return;

	ext = (MonoClassExt *)mono_class_alloc0 (klass, sizeof (MonoClassExt));
	mono_image_lock (klass->image);
	mono_memory_barrier ();
	if (!klass->ext)
		klass->ext = ext;
	class_ext_size += sizeof (MonoClassExt);
	mono_image_unlock (klass->image);
}
