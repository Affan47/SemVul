unpackmem(char *valp, uint32_t * size_valp, Buf buffer)
{
	uint32_t ns;

	if (remaining_buf(buffer) < sizeof(ns))
		return SLURM_ERROR;

	memcpy(&ns, &buffer->head[buffer->processed], sizeof(ns));
	*size_valp = ntohl(ns);
	buffer->processed += sizeof(ns);

	if (*size_valp > MAX_PACK_MEM_LEN)
		return SLURM_ERROR;
	else if (*size_valp > 0) {
		if (remaining_buf(buffer) < *size_valp)
			return SLURM_ERROR;
		memcpy(valp, &buffer->head[buffer->processed], *size_valp);
		buffer->processed += *size_valp;
	} else
		*valp = 0;
	return SLURM_SUCCESS;
}
