get_default_mirror(struct mirror_set *ms)
{
	return &ms->mirror[atomic_read(&ms->default_mirror)];
}
