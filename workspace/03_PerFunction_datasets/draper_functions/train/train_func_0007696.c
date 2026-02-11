clancore_resource_added(CL_Resource &resource)
{
	std::string type = resource.get_type();

	if (type == "boolean") new CL_ResourceData_Boolean(resource);
	if (type == "integer") new CL_ResourceData_Integer(resource);
	if (type == "float") new CL_ResourceData_Float(resource);
	if (type == "string") new CL_ResourceData_String(resource);
	if (type == "raw") new CL_ResourceData_Raw(resource);
}
