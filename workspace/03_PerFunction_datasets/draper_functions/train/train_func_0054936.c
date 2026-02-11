dynv_var_float_deserialize(struct dynvVariable* variable, struct dynvIO* io){
	uint32_t read;
	uint32_t size;
	dynv_io_read(io, &size, 4, &read);

    union{
		uint32_t i32;
		float f32;
	}value;

    if (dynv_io_read(io, &value, 4, &read)==0){
		if (read == 4){
			value.i32 = UINT32_FROM_LE(value.i32);
			variable->float_value = value.f32;
			return 0;
		}
	}
	return -1;
}
