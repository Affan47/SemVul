_update_vg_lock_count(const char *resource, uint32_t flags)
{

	if ((flags & LCK_SCOPE_MASK) != LCK_VG ||
	    (flags & LCK_CACHE) ||
	    !strcmp(resource, VG_GLOBAL))
		return;

	if ((flags & LCK_TYPE_MASK) == LCK_UNLOCK)
		_vg_lock_count--;
	else
		_vg_lock_count++;


	if ((flags & LCK_TYPE_MASK) == LCK_WRITE)
		_vg_write_lock_held = 1;
	else if (!_vg_lock_count)
		_vg_write_lock_held = 0;
}
