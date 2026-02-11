mono_class_has_finalizer (MonoClass *klass)
{
	gboolean has_finalize = FALSE;

	if (klass->has_finalize_inited)
		return klass->has_finalize;


	if (!(MONO_CLASS_IS_INTERFACE (klass) || klass->valuetype)) {
		MonoMethod *cmethod = NULL;

		if (klass->rank == 1 && klass->byval_arg.type == MONO_TYPE_SZARRAY) {
		} else if (klass->generic_class) {
			MonoClass *gklass = klass->generic_class->container_class;

			has_finalize = mono_class_has_finalizer (gklass);
		} else if (klass->parent && klass->parent->has_finalize) {
			has_finalize = TRUE;
		} else {
			if (klass->parent) {


				mono_class_setup_vtable (klass);
				if (klass->exception_type || mono_loader_get_last_error ())
					cmethod = NULL;
				else
					cmethod = klass->vtable [finalize_slot];
			}

			if (cmethod) {
				g_assert (klass->vtable_size > finalize_slot);

				if (klass->parent) {
					if (cmethod->is_inflated)
						cmethod = ((MonoMethodInflated*)cmethod)->declaring;
					if (cmethod != default_finalize)
						has_finalize = TRUE;
				}
			}
		}
	}

	mono_image_lock (klass->image);

	if (!klass->has_finalize_inited) {
		klass->has_finalize = has_finalize ? 1 : 0;

		mono_memory_barrier ();
		klass->has_finalize_inited = TRUE;
	}

	mono_image_unlock (klass->image);

	return klass->has_finalize;
}
