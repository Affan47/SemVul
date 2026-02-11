topology_phys_to_logical_pkg(unsigned int phys_pkg)
{
	if (phys_pkg >= max_physical_pkg_id)
		return -1;
	return physical_to_logical_pkg[phys_pkg];
}
