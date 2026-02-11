temp_kvs_add(char *key, char *val)
{
	Buf buf;
	uint32_t size;

	if ( key == NULL || val == NULL )
		return SLURM_SUCCESS;

	buf = init_buf(PMI2_MAX_KEYLEN + PMI2_MAX_VALLEN + 2 * sizeof(uint32_t));
	packstr(key, buf);
	packstr(val, buf);
	size = get_buf_offset(buf);
	if (temp_kvs_cnt + size > temp_kvs_size) {
		temp_kvs_size += TEMP_KVS_SIZE_INC;
		xrealloc(temp_kvs_buf, temp_kvs_size);
	}
	memcpy(&temp_kvs_buf[temp_kvs_cnt], get_buf_data(buf), size);
	temp_kvs_cnt += size;
	free_buf(buf);

	return SLURM_SUCCESS;
}
