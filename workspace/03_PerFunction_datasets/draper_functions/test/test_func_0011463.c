dynv_var_int32_serialize(struct dynvVariable* variable, struct dynvIO* io){
	uint32_t written;

	uint32_t length=4;
	length = UINT32_TO_LE(length);

	dynv_io_write(io, &length, 4, &written);

	int32_t value = UINT32_TO_LE(variable->int_value);
	if (dynv_io_write(io, &value, 4, &written)==0){
		if (written == 4) return 0;
	}
	return -1;
}
