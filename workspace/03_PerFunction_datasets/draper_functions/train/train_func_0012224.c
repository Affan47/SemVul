mono_aot_get_offset (guint32 *table, int index)
{
	int i, group, ngroups, index_entry_size;
	int start_offset, offset, group_size;
	guint8 *data_start, *p;
	guint32 *index32 = NULL;
	guint16 *index16 = NULL;


	group_size = table [1];
	ngroups = table [2];
	index_entry_size = table [3];
	group = index / group_size;

	if (index_entry_size == 2) {
		index16 = (guint16*)&table [4];
		data_start = (guint8*)&index16 [ngroups];
		p = data_start + index16 [group];
	} else {
		index32 = (guint32*)&table [4];
		data_start = (guint8*)&index32 [ngroups];
		p = data_start + index32 [group];
	}


	offset = start_offset = decode_value (p, &p);
	for (i = group * group_size + 1; i <= index; ++i) {
		offset += decode_value (p, &p);
	}


	return offset;
}
