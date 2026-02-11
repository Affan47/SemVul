get_class_name(const std::string &type)
{
	std::map<std::string, CL_ComponentType *>::const_iterator it(component_types.find(type));
	if (it == component_types.end()) cl_throw_error(std::string("Could not find component type ") + type);

	return it->second->get_class_name();
}
