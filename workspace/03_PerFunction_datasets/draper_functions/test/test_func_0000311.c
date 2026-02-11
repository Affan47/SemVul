dynv_io_memory_read(struct dynvIO* io, void* data, uint32_t size, uint32_t* data_read){
	struct dynvMemoryIO* mem_io = (struct dynvMemoryIO*) io->userdata;

	uint32_t data_left = mem_io->eof - mem_io->position;
	if (size > data_left)
		size = data_left;
	memcpy(data, mem_io->buffer + mem_io->position, size);
	mem_io->position += size;
	*data_read=size;
	return 0;
}
