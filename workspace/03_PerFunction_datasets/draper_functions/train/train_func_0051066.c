__get_system_dir(struct trace_subsystem_dir *dir)
{
	WARN_ON_ONCE(dir->ref_count == 0);
	dir->ref_count++;
	__get_system(dir->subsystem);
}
