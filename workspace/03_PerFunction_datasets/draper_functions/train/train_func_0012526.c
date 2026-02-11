next_unit(struct pt3_adapter *adap, int *idx, int *ofs)
{
	*ofs += PT3_ACCESS_UNIT;
	if (*ofs >= DATA_BUF_SZ) {
		*ofs -= DATA_BUF_SZ;
		(*idx)++;
		if (*idx == adap->num_bufs)
			*idx = 0;
	}
	return &adap->buffer[*idx].data[*ofs];
}
