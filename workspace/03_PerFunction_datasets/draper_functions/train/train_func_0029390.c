mono_security_core_clr_check_inheritance (MonoClass *class)
{
	MonoSecurityCoreCLRLevel class_level, parent_level;
	MonoClass *parent = class->parent;

	if (!parent)
		return;

	class_level = mono_security_core_clr_class_level (class);
	parent_level = mono_security_core_clr_class_level (parent);

	if (class_level < parent_level) {
		set_type_load_exception_type (
			"Inheritance failure for type %s. Parent class %s is more restricted.",
			class);
	} else {
		MonoMethod *parent_ctor = get_default_ctor (parent);
		if (parent_ctor && ((parent_ctor->flags & METHOD_ATTRIBUTE_PUBLIC) != 0)) {
			class_level = mono_security_core_clr_method_level (get_default_ctor (class), FALSE);
			parent_level = mono_security_core_clr_method_level (parent_ctor, FALSE);
			if (class_level < parent_level) {
				set_type_load_exception_type (
					"Inheritance failure for type %s. Default constructor security mismatch with %s.",
					class);
			}
		}
	}
}
