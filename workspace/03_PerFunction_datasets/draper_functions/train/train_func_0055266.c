mono_class_has_gtd_parent (MonoClass *klass, MonoClass *parent)
{
	klass = mono_class_get_generic_type_definition (klass);
	parent = mono_class_get_generic_type_definition (parent);
	mono_class_setup_supertypes (klass);
	mono_class_setup_supertypes (parent);

	return klass->idepth >= parent->idepth &&
		mono_class_get_generic_type_definition (klass->supertypes [parent->idepth - 1]) == parent;
}
