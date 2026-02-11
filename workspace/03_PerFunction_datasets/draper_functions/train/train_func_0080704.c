unpack8(uint8_t * valp, Buf buffer)
{
	if (remaining_buf(buffer) < sizeof(uint8_t))
		return SLURM_ERROR;

	memcpy(valp, &buffer->head[buffer->processed], sizeof(uint8_t));
	buffer->processed += sizeof(uint8_t);
	return SLURM_SUCCESS;
}
