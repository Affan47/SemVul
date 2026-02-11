log_from_idx(char *log_buf, uint32_t idx)
{
	char *msg = log_buf + idx;


	if (!struct_val_u16(msg, log_offset_len))
		return log_buf;
	return msg;
}
