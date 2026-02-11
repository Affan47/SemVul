debug_unregister_domain(const std::string& domain)
{
	using namespace debug_internal;
	DebugState::domain_map_t& dm = get_debug_state().get_domain_map();

	DebugState::domain_map_t::iterator found = dm.find(domain);
	if (found == dm.end())
		return false;

	dm.erase(found);
	return true;
}
