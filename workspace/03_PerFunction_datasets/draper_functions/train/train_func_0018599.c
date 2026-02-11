scrub_contexts()
{
	std::set<context *>::const_iterator begin = active_contexts.begin();
	std::set<context *>::const_iterator end = active_contexts.end();
	while(begin != end)
	{
		scrub_context(*begin);
		begin++;
	}
}
