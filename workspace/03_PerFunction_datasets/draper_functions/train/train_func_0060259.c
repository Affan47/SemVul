ves_icall_System_GC_SuppressFinalize (MonoObject *obj)
{
	MONO_CHECK_ARG_NULL (obj,);


	if (obj->vtable->klass->delegate)
		return;


	object_register_finalizer (obj, NULL);
}
