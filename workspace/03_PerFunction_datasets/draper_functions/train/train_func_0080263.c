setsystime_vblank (void)
{
	Unit *u;
	for (u = units; u; u = u->next) {
		if (is_virtual (u->unit) && filesys_isvolume (u)) {
			put_byte (u->volume + 173 - 32, 1);
			uae_Signal (get_long (u->volume + 176 - 32), 1 << 13);
			break;
		}
	}
}
