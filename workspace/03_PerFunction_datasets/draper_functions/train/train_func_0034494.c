get_assembly_name (MonoErrorInternal *error)
{
	if (error->assembly_name)
		return error->assembly_name;
	if (error->klass && error->klass->image)
		return error->klass->image->name;
	return "<unknown assembly>";
}
