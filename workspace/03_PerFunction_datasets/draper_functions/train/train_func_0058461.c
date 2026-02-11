mono_class_get_generic_type_definition (MonoClass *klass)
{
	return klass->generic_class ? klass->generic_class->container_class : klass;
}
