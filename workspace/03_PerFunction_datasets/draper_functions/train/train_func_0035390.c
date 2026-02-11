mono_remote_class_vtable (MonoDomain *domain, MonoRemoteClass *remote_class, MonoRealProxy *rp)
{
	MONO_REQ_GC_UNSAFE_MODE;

	mono_loader_lock ();
	mono_domain_lock (domain);
	if (rp->target_domain_id != -1) {
		if (remote_class->xdomain_vtable == NULL)
			remote_class->xdomain_vtable = mono_class_proxy_vtable (domain, remote_class, MONO_REMOTING_TARGET_APPDOMAIN);
		mono_domain_unlock (domain);
		mono_loader_unlock ();
		return remote_class->xdomain_vtable;
	}
	if (remote_class->default_vtable == NULL) {
		MonoType *type;
		MonoClass *klass;
		type = ((MonoReflectionType *)rp->class_to_proxy)->type;
		klass = mono_class_from_mono_type (type);
#ifndef DISABLE_COM
		if ((mono_class_is_com_object (klass) || (mono_class_get_com_object_class () && klass == mono_class_get_com_object_class ())) && !mono_vtable_is_remote (mono_class_vtable (mono_domain_get (), klass)))
			remote_class->default_vtable = mono_class_proxy_vtable (domain, remote_class, MONO_REMOTING_TARGET_COMINTEROP);
		else
#endif
			remote_class->default_vtable = mono_class_proxy_vtable (domain, remote_class, MONO_REMOTING_TARGET_UNKNOWN);
	}

	mono_domain_unlock (domain);
	mono_loader_unlock ();
	return remote_class->default_vtable;
}
