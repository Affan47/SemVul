set_interface_and_offset (int num_ifaces, MonoClass **interfaces_full, int *interface_offsets_full, MonoClass *ic, int offset, mono_bool force_set)
{
	int i = find_interface (num_ifaces, interfaces_full, ic);
	if (i >= 0) {
		if (!force_set)
			return TRUE;
		interface_offsets_full [i] = offset;
		return FALSE;
	}
	for (i = 0; i < num_ifaces; ++i) {
		if (interfaces_full [i]) {
			int end;
			if (interfaces_full [i]->interface_id < ic->interface_id)
				continue;
			end = i + 1;
			while (end < num_ifaces && interfaces_full [end]) end++;
			memmove (interfaces_full + i + 1, interfaces_full + i, sizeof (MonoClass*) * (end - i));
			memmove (interface_offsets_full + i + 1, interface_offsets_full + i, sizeof (int) * (end - i));
		}
		interfaces_full [i] = ic;
		interface_offsets_full [i] = offset;
		break;
	}
	return FALSE;
}
