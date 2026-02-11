dynv_io_memory_write(struct dynvIO* io, void* data, uint32_t size, uint32_t* data_written) {
	struct dynvMemoryIO* mem_io = (struct dynvMemoryIO*) io->userdata;

	uint32_t data_left = mem_io->size - mem_io->position;
	if (data_left < size){
		uint32_t new_buf = mem_io->size + size + 4096;


		char *nb;
		if ((nb = new char[new_buf])){
			if (mem_io->buffer){
				memcpy(nb, mem_io->buffer, mem_io->position);
				delete[] mem_io->buffer;
			}
			mem_io->buffer = nb;
			mem_io->size = new_buf;
		}else{
			*data_written = 0;
			return 0;
		}
	}
	memcpy(mem_io->buffer + mem_io->position, data, size);
	mem_io->position += size;
	if (mem_io->position > mem_io->eof)
		mem_io->eof = mem_io->position;
	*data_written = size;
	return 0;
}
